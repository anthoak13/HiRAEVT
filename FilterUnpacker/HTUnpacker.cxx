#include "HTUnpacker.h"

#include "TFile.h"
#include "TTree.h"

#include "HTExperiment.h"
#include "HTExperimentInfo.h"
#include "HTUnpackerFactory.h"

#include <CFilter.h>
#include <CPhysicsEventItem.h>
#include <CRingStateChangeItem.h>
#include <FragmentIndex.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string.h>

HTUnpacker::HTUnpacker(json configJson, Int_t runNum, ULong_t fileLength) : fEventUnpacked(0), fFileLength(fileLength)
{
   // Get the experiment name
   fExperimentInfo = new HTExperimentInfo(configJson["experimentNumber"].get<Int_t>());
   fExperiment = new HTExperiment(configJson["experimentNumber"].get<Int_t>());

   try {
      kMergedData = configJson["mergedData"].get<bool>();
   } catch (std::exception e) {
      std::cout << "Assuming unmerged data" << std::endl;
      kMergedData = false;
   }

   // Create the output file and tree
   fOutFile = new TFile(
      TString::Format("%s/run-%d.root", configJson["outputDirectory"].get<std::string>().c_str(), runNum), "RECREATE");
   fOutTree = new TTree(fExperiment->GetName(), fExperimentInfo->GetRunTitle());

   // Create the unpackers and register the output on the tree
   CreateUnpackers(configJson["VMEstacks"]);

   // Get the start time of unpacking
   fStartTime = time(nullptr);
}

HTUnpacker::~HTUnpacker() {}

void HTUnpacker::CreateUnpackers(json stackList)
{
   std::cout << "Creating all unpackers" << std::endl;
   for (auto &stack : stackList) {

      // Get the stack ID and create the stack
      Int_t stackID = stack["stackID"].get<int>();
      std::cout << "Creating stack with ID: " << stackID << std::endl;
      std::vector<HTModuleUnpacker *> moduleList;

      for (auto &module : stack["modules"]) {

         std::cout << "Creating module: " << module << std::endl;
         // Register RootModule
         moduleList.push_back(HTUnpackerFactory::Instance()->CreateUnpacker(module, fOutTree));
         // fExperiment->RegisterModule(moduleList.back()->GetRootModule());
      }
      stackMap[stackID] = moduleList;

      // Set fBufferMismatchcount vectors
      fBufferMismatchCount[stackID] = 0;
   }
}

// handle the state change events
CRingItem *HTUnpacker::handleStateChangeItem(CRingStateChangeItem *pItem)
{
   TDatime time(pItem->getTimestamp());

   switch (pItem->type()) {

      // Its a begin run event, so save the run number, time, and title
   case 1:
      std::cout << "Begin run " << pItem->getRunNumber() << " at " << time.AsString() << std::endl;
      fExperimentInfo->SetStartTime(time);
      fExperimentInfo->SetRunNumber(pItem->getRunNumber());
      fExperimentInfo->SetRunTitle(pItem->getTitle());
      break;

      // It's a end run event to save the end time
   case 2:
      std::cout << "End run " << pItem->getRunNumber() << " at " << time.AsString() << std::endl;
      fExperimentInfo->SetEndTime(time);

      std::cout << "Writing experiment info" << std::endl;
      fExperimentInfo->Write();
      std::cout << "Writing experiment data" << std::endl;
      fOutTree->Write();
      std::cout << "Closing file" << std::endl;
      fOutFile->Close();
      break;
   default: break;
   }

   return pItem;
}

// handle the physics events
CRingItem *HTUnpacker::handlePhysicsEventItem(CPhysicsEventItem *pItem)
{
   uint16_t *pBody = reinterpret_cast<uint16_t *>(pItem->getBodyPointer());
   (fEventUnpacked)++;

   // if(fEventUnpacked > 2) return pItem;

   if (fEventUnpacked % 1000 == 0)
      PrintPercentage();

   if (kMergedData) {
      // Deal with the built data structure
      // if the physics event item is not the output of the
      // event builder, you don't need this.
      FragmentIndex frags(pBody);

      // Loop through fragments
      for (auto it = frags.begin(); it != frags.end(); it++) {
         // TODO: Re-implement timstamp checking like Unpack.cpp lines 164-173

         // Get the stack to unpack
         auto stack = stackMap.find(it->s_sourceId);
         if (stack == stackMap.end()) {
            std::cout << "Couldn't find stack with ID: " << it->s_sourceId << std::endl;
            continue;
         }

         // Unpack the USB stack
         UnpackStack(it->s_itembody, it->s_size);

      } // end loop over fragments
   } else {

      UnpackStack(pBody, pItem->getBodySize());
      // Increase total unpacked words by bodysize/2
      //(*unpacker)(pBody, pItem->getBodySize());
   }
   fOutTree->Fill();

   // return the original item
   return pItem;
}

void HTUnpacker::UnpackStack(UShort_t *pEvent, UInt_t eventSize)
{
   vector<UShort_t> event;

   // Define useful flags for VMSUB header decoding
   const UShort_t VMUSB_CONTINUE = 0x1000;
   const UShort_t VMUSB_STACKID_MASK = 0xe000;
   const UShort_t VMUSB_STACKID_SHIFT = 13;
   const UShort_t VMUSB_LENGTH = 0x0fff;

   // Get the header, stack size
   UShort_t header = *pEvent++;
   Int_t stackID = (header & VMUSB_STACKID_MASK) << VMUSB_STACKID_SHIFT;
   UShort_t stackSizeWords = header & VMUSB_LENGTH;
   auto stackSizeBytes = 2 * (stackSizeWords + 1);
   fWordsUnpacked++;

   if ((header & VMUSB_CONTINUE) != 0) {
      std::cout << "Didn't get a continue on event " << fEventUnpacked << std::endl;
   }

   if (eventSize != stackSizeBytes) {
      std::cerr << "Mismatch in sizes: " << eventSize << " " << stackSizeBytes << std::endl;
      return;
   }

   for (int i = 0; i < stackSizeWords; i++) {
      UShort_t datum = *pEvent++;
      event.push_back(datum);
   }

   UInt_t offset = 0;
   for (auto &module : stackMap.at(stackID)) {
      // Clear any extra 0xffffs
      while (event[offset] == 0xffff)
         ++offset;

      // Make sure we're not at the end of the event
      if (offset > event.size() - 2)
         break;

      ULong_t header = getLong(event, offset);
      Int_t vsn = module->DecodeVSN(header);

      if (vsn == module->GetVSN() || vsn == -1)
         offset = module->Unpack(event, offset);
      /*      else
          std::cout << "Skipping unpacking of " << std::dec << vsn << " "
               << module->GetName() << std::endl;
      */

      // module->GetRootModule()->PrintData();
      // std::cout << std::endl;
   }

   // Clear remaining ffffs
   while (event[offset] == 0xffff)
      ++offset;

   fWordsUnpacked += event.size();
   if (offset < event.size()) {
      // std::cout << "Event not unpacked fully" << std::endl;
      // std::cout << "Unpacked " << offset << " but is size " << event.size() << std::endl;
      fBufferMismatchCount[stackID]++;
   }
}

ULong_t HTUnpacker::getLong(std::vector<UShort_t> &event, ULong_t offset)
{
   ULong_t low = event[offset];
   ULong_t high = event[offset + 1];
   return low | (high << 16);
}

void HTUnpacker::PrintSummary()
{
   std::cout << "Unpacked " << fEventUnpacked << " events." << std::endl << std::endl;
   for (auto &stack : stackMap) {
      std::cout << TString::Format("---- Stack %d ----", stack.first) << std::endl;
      std::cout << TString::Format("BufferMismatches: %lu", fBufferMismatchCount.at(stack.first)) << std::endl
                << std::endl;
      for (auto &module : stack.second)
         module->PrintSummary();
   }
}

void HTUnpacker::PrintPercentage() const
{
   // Get the time elapsed
   TDatime now = time(nullptr);
   UInt_t time_elapsed = now.Convert() - fStartTime.Convert();

   std::cout << "Percentage= " << std::fixed << std::setprecision(1) << std::setw(5)
             << 100 * (2 * fWordsUnpacked) / fFileLength << " %   [";

   // Get the number of ='s to print and print them
   int numToPrint = 20 * (2 * fWordsUnpacked) / fFileLength;
   for (int i = 0; i < 20; ++i)
      if (i < numToPrint)
         std::cout << "=";
      else
         std::cout << " ";
   std::cout << "]   ";

   // Print the elapsed time
   std::cout << "elapsed time: "
             << (time_elapsed < 60 ? time_elapsed : (time_elapsed < 3600 ? time_elapsed / 60 : time_elapsed / 3600))
             << (time_elapsed < 60 ? " s; " : (time_elapsed < 3600 ? " m; " : " h; "));

   // Get the remaining time and print it
   if (fWordsUnpacked > 2) {
      ULong_t remainingFileSize = fFileLength - 2 * fWordsUnpacked;
      Double_t secondsPerWord = (double)time_elapsed / (2 * fWordsUnpacked);

      Double_t time_remaining = remainingFileSize * secondsPerWord;
      std::cout << "Estimated remaining time: "
                << (time_remaining < 60 ? time_remaining
                                        : (time_remaining < 3600 ? time_remaining / 60 : time_remaining / 3600))
                << (time_remaining < 60 ? " s      " : (time_remaining < 3600 ? " m      " : " h      "));
   } // End if we should displat remaining time

   std::cout << "\r";
   std::cout.flush();
   // std::cout << std::endl;
}
