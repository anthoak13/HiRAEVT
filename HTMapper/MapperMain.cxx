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
  auto confVal = std::getenv("HiRAEVTCONFIG");
  if (confVal == nullptr)
  {
    cout << "Envirment not configured for config file" << endl;
    exit(-1);
  }
  std::string configFile(confVal);

  printf("** Initializing Mapper **\n");
  std::cout << "Loading config file: " << configFile << std::endl;

  
  if( TheMapper->InitializeMapper(configFile.c_str())!= 0 )
  {
      printf("Error while configuring program\n");
    return -2;
  }
  
  printf("** Mapper correctly initialized **\n");

  //Create HTRawDataReader object
  HTRawDataReader * TheReader = new HTRawDataReader(TheMapper);

  printf("** Initializing Reader **\n");

  //Initialize HTRawDataReader object
  if(TheReader->InitReader()!=0) {
    printf("Error while initializing HTRawDataReader class\n");
    TheReader->EndProcess();
    return -3;
  }
  printf("** Reader correctly initialized **\n");


  //Main loop HTRawDataReader::ProcessRawTree()
  printf("** Mapping run %d **\n", HTExperimentInfo::Instance()->GetRunInfo()->GetRunNumber());
  TheReader->ProcessRawTree();


  //End mapping process HTRawDataReader::EndProcess()
  TheReader->EndProcess();

  return 0;
}
