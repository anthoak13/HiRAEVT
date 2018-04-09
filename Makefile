CXXFLAGS = -g

all:
	$(MAKE) root
	@ln -sf libRBSetup.so.1.0 libRBSetup.so.1
	@ln -sf libRBSetup.so.1 libRBSetup.so
	@mv libRBSetup.so $(RIBbitLIB)/.
	@mv libRBSetup.so.1 $(RIBbitLIB)/.
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  ;		$(MAKE) -C FilterUnpacker install
endif

root:
	$(MAKE) -C utilities ;	 		$(MAKE) -C utilities install
	$(MAKE) -C electronics ; 		$(MAKE) -C electronics install
	$(MAKE) -C detectors/RBDetector ; 	$(MAKE) -C detectors/RBDetector install
	$(MAKE) -C detectors/RBHiRA ; 		$(MAKE) -C detectors/RBHiRA install
	$(MAKE) -C detectors/RBS800 ; 		$(MAKE) -C detectors/RBS800 install
	$(MAKE) -C detectors/RBMcp ; 		$(MAKE) -C detectors/RBMcp install
	$(MAKE) -C detectors/RBNeutronWall ;	$(MAKE) -C detectors/RBNeutronWall install
	$(MAKE) -C detectors/RBMicroball ;	$(MAKE) -C detectors/RBMicroball install	
	$(MAKE) -C detectors/RBForwardArray ;	$(MAKE) -C detectors/RBForwardArray install	
	$(MAKE) -C RBExperiment ; 		$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup ;			$(MAKE) -C RBSetup install

install:
	$(MAKE) -C utilities
	$(MAKE) -C electronics install
	$(MAKE) -C detectors/RBDetector install
	$(MAKE) -C detectors/RBHiRA install
	$(MAKE) -C detectors/RBS800 install
	$(MAKE) -C detectors/RBMcp install
	$(MAKE) -C detectors/RBNeutronWall install
	$(MAKE) -C detectors/RBMicroball install
	$(MAKE) -C detectors/RBForwardArray install
	$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup install
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  install
endif

distclean:
	$(MAKE) -C utilities distclean
	$(MAKE) -C electronics distclean
	$(MAKE) -C detectors/RBDetector distclean

	$(MAKE) -C detectors/RBHiRA distclean
	$(MAKE) -C detectors/RBS800 distclean
	$(MAKE) -C detectors/RBMcp distclean
	$(MAKE) -C detectors/RBNeutronWall distclean
	$(MAKE) -C detectors/RBMicroball distclean
	$(MAKE) -C detectors/RBForwardArray distclean
	$(MAKE) -C RBExperiment distclean
	$(MAKE) -C RBSetup distclean
	@rm $(RIBbitLIB)/libRBSetup.so
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  distclean
endif

clean:
	$(MAKE) -C utilities clean
	$(MAKE) -C electronics  clean
	$(MAKE) -C detectors/RBDetector clean
	$(MAKE) -C detectors/RBHiRA clean
	$(MAKE) -C detectors/RBS800 clean
	$(MAKE) -C detectors/RBMcp clean
	$(MAKE) -C detectors/RBNeutronWall clean
	$(MAKE) -C detectors/RBMicroball clean
	$(MAKE) -C detectors/RBForwardArray clean
	$(MAKE) -C RBExperiment clean
	$(MAKE) -C RBSetup clean
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  clean
endif

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C utilities
	$(MAKE) -C electronics
	$(MAKE) -C detectors/RBDetector
	$(MAKE) -C detectors/RBHiRA
	$(MAKE) -C detectors/RBS800
	$(MAKE) -C detectors/RBMcp
	$(MAKE) -C detectors/RBNeutronWall
	$(MAKE) -C detectors/RBMicroball
	$(MAKE) -C detectors/RBForwardArray
	$(MAKE) -C RBExperiment 
	$(MAKE) -C RBSetup 
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker 
endif
