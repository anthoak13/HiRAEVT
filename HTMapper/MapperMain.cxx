#include <stdio.h>
#include <stdlib.h>

#include <HiRAEVTLogo.h>
#include <HTShared.h>
#include <HTRunInfo.h>
#include <HTMapper.h>
#include <HTRawDataReader.h>

int main (int argc, char ** argv)
{
  //Print program logo
  PrintHiRAEVTMapperLogo();

  //Create a new HTMapper object
  HTMapper * TheMapper = new HTMapper();

  //Pass Argument to HTMapper object and retrieve run number to analyze
  if(TheMapper->PassArguments(argc,argv)<0) {
    printf("Error: run number was not specified with the --run command\n");
    return -1;
  }

  //Initialize HTMapper object
  printf("** Initializing Mapper **\n");
  if(TheMapper->InitializeMapper("config/HiRAEVT.conf")!=0) {
    printf("Error while configuring program\n");
    return -2;
  }
  printf("** Mapper correctly initialized **\n");

  //Create HTRawDataReader object
  HTRawDataReader * TheReader = new HTRawDataReader();

  printf("** Initializing Reader **\n");
  //Set Mapper to HTRawDataReader object
  TheReader->SetMapper(TheMapper);

  //Initialize HTRawDataReader object
  if(TheReader->InitReader()!=0) {
    printf("Error while initializing HTRawDataReader class\n");
    TheReader->EndProcess();
    return -3;
  }
  printf("** Reader correctly initialized **\n");


  //Main loop HTRawDataReader::ProcessRawTree()
  printf("** Mapping run %d **\n", gRun->GetRunNumber());
  TheReader->ProcessRawTree();


  //End mapping process HTRawDataReader::EndProcess()
  TheReader->EndProcess();

  return 0;
}
