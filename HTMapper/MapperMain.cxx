#include <stdio.h>
#include <stdlib.h>

#include <HiRAEVTLogo.h>
#include <HTMapper.h>

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
  if(TheMapper->InitializeMapper("config/HiRAEVT.conf")!=0) {
    printf("Error: error while configuring program\n");
    return -2;
  }

  //Create HTRawDataReader object

  //Initialize HTRawDataReader object

  //Set Mapper to HTRawDataReader object


  //Main loop HTRawDataReader::ProcessRawTree()


  //End mapping process HTRawDataReader::EndProcess()

  return 0;
}
