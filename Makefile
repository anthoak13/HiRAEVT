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
	$(MAKE) -C electronics ; 		$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment ; 		$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup ;			$(MAKE) -C RBSetup install
	$(MAKE) -C logo ;			$(MAKE) -C logo install

install:
	$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment install
	$(MAKE) -C RBSetup install
	$(MAKE) -C logo install
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  install
endif

distclean:
	$(MAKE) -C electronics distclean
	$(MAKE) -C RBExperiment distclean
	$(MAKE) -C RBSetup distclean
	$(MAKE) -C logo distclean
	@rm $(RIBbitLIB)/libRBSetup.so
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  distclean
endif

clean:
	$(MAKE) -C electronics  clean
	$(MAKE) -C RBExperiment clean
	$(MAKE) -C RBSetup clean
	$(MAKE) -C logo clean
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker  clean
endif

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C electronics
	$(MAKE) -C RBExperiment
	$(MAKE) -C RBSetup
	$(MAKE) -C logo
ifdef DAQROOT
	$(MAKE) -C FilterUnpacker
endif
