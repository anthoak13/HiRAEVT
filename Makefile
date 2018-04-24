CXXFLAGS = -g

all:
	$(MAKE) root
	$(MAKE) -C FilterUnpacker  ;		$(MAKE) -C FilterUnpacker install
	$(MAKE) -C HTMapper ;			$(MAKE) -C HTMapper install

root:
	$(MAKE) -C electronics ; 		$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment ; 		$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup ;			$(MAKE) -C RBSetup install
	$(MAKE) -C logo ;			$(MAKE) -C logo install
	$(MAKE) -C shared ;			$(MAKE) -C shared install
	$(MAKE) -C HTRunInfo ;			$(MAKE) -C HTRunInfo install
	$(MAKE) -C HTDetectorMap ;			$(MAKE) -C HTDetectorMap install
	$(MAKE) -C HTExperimentalSetup ;			$(MAKE) -C HTExperimentalSetup install
	$(MAKE) -C HTRootElectronics ;			$(MAKE) -C HTRootElectronics install
	$(MAKE) -C detectors/HTDetector ;			$(MAKE) -C detectors/HTDetector install

install:
	$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup install
	$(MAKE) -C logo install
	$(MAKE) -C shared install
	$(MAKE) -C HTRunInfo install
	$(MAKE) -C HTDetectorMap install
	$(MAKE) -C HTExperimentalSetup install
	$(MAKE) -C HTRootElectronics install
	$(MAKE) -C detectors/HTDetector install

distclean:
	$(MAKE) -C electronics distclean
	$(MAKE) -C RBExperiment distclean
	$(MAKE) -C RBSetup distclean
	$(MAKE) -C logo distclean
	$(MAKE) -C shared distclean
	$(MAKE) -C HTRunInfo distclean
	$(MAKE) -C HTDetectorMap distclean
	$(MAKE) -C HTExperimentalSetup distclean
	$(MAKE) -C HTRootElectronics distclean
	$(MAKE) -C detectors/HTDetector distclean

	$(MAKE) -C FilterUnpacker  distclean
	$(MAKE) -C HTMapper  distclean

clean:
	$(MAKE) -C electronics  clean
	$(MAKE) -C RBExperiment clean
	$(MAKE) -C RBSetup clean
	$(MAKE) -C logo clean
	$(MAKE) -C shared clean
	$(MAKE) -C HTRunInfo clean
	$(MAKE) -C HTDetectorMap clean
	$(MAKE) -C HTExperimentalSetup clean
	$(MAKE) -C HTRootElectronics clean
	$(MAKE) -C detectors/HTDetector clean

	$(MAKE) -C FilterUnpacker  clean
	$(MAKE) -C HTMapper  clean

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C electronics
	$(MAKE) -C RBExperiment
	$(MAKE) -C RBSetup
	$(MAKE) -C logo
	$(MAKE) -C shared
	$(MAKE) -C HTRunInfo
	$(MAKE) -C HTDetectorMap
	$(MAKE) -C HTExperimentalSetup
	$(MAKE) -C HTRootElectronics
	$(MAKE) -C detectors/HTDetector

	$(MAKE) -C FilterUnpacker
	$(MAKE) -C HTMapper  clean
