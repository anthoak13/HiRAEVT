
#include <iostream>
#include <CFatalException.h>
#include <CFilterMain.h>

#include <CUnpackerFilter.h>
#include <HiRAEVTLogo.h>
#include <HTShared.h>
#include <Unpacker.h>

/// The main function
/**! main function
  Creates a CFilterMain object and
  executes its operator()() method.

  \return 0 for normal exit,
          1 for known fatal error,
          2 for unknown fatal error
*/
int main(int argc, char* argv[])
{
    PrintHiRAEVTUnpackerLogo();

    int status = 0;

    // Create the main
    CFilterMain theApp(argc,argv);
    std::cout <<"**Main app created**" << std::endl;
    //    std::cout <<"**Argc is " << argc  << std::endl;
    // Construct filter(s) here.
    CUnpackerFilter unpacker_filter;
    // Pass along the command-line arguments to the unpacker.
    unpacker_filter.PassArguments(argc, argv);
    std::cout << "**Unpacker filter intialized**" << std::endl;

    // Register the filter(s) here. Note that if more than
    // one filter will be registered, the order of registration
    // will define the order of execution. If multiple filters are
    // registered, the output of the first filter will become the
    // input of the second filter and so on.
    theApp.registerFilter(&unpacker_filter);
    std::cout << "**Unpacker filter registered**" << std::endl;

    // Run the main loop
    theApp();
    
    // End unpacking process
    gUnpacker->EndUnpacking();

  return status;
}
