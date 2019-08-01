CXXFLAGS = -g

all:
	$(MAKE) root
	$(MAKE) -C FilterUnpacker  ;		$(MAKE) -C FilterUnpacker install
	$(MAKE) -C HTMapper ;			$(MAKE) -C HTMapper install

root:
	$(MAKE) -C electronics ; 			$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment ; 			$(MAKE) -C RBExperiment install
	$(MAKE) -C logo ;				$(MAKE) -C logo install
	$(MAKE) -C HTRunInfo ;				$(MAKE) -C HTRunInfo install
	$(MAKE) -C HTRootElectronics ;			$(MAKE) -C HTRootElectronics install
	$(MAKE) -C detectors/HTDetector ;		$(MAKE) -C detectors/HTDetector install
	$(MAKE) -C detectors/HTSisTimestampe15190 ;	$(MAKE) -C detectors/HTSisTimestampe15190 install
	$(MAKE) -C detectors/HTHiRA ;			$(MAKE) -C detectors/HTHiRA install
	$(MAKE) -C detectors/HTNeutronWall ;		$(MAKE) -C detectors/HTNeutronWall install
	$(MAKE) -C detectors/HTVetoWall ;		$(MAKE) -C detectors/HTVetoWall install
	$(MAKE) -C detectors/HTForwardArray ;		$(MAKE) -C detectors/HTForwardArray install
	$(MAKE) -C detectors/HTMicroball ;		$(MAKE) -C detectors/HTMicroball install
	$(MAKE) -C detectors/HTTDCSpare ;		$(MAKE) -C detectors/HTTDCSpare install
	$(MAKE) -C detectors/HTIonChamber ;		$(MAKE) -C detectors/HTIonChamber install
	$(MAKE) -C HTCalibration ; 			$(MAKE) -C HTCalibration install	
	$(MAKE) -C HTExperimentalSetup ;		$(MAKE) -C HTExperimentalSetup install	
	$(MAKE) -C HTRawDataReader ; 			$(MAKE) -C HTRawDataReader install


install:
	$(MAKE) -C electronics install
	$(MAKE) -C RBExperiment install
	$(MAKE) -C logo install
	$(MAKE) -C HTRunInfo install
	$(MAKE) -C HTRootElectronics install
	$(MAKE) -C detectors/HTDetector install
	$(MAKE) -C detectors/HTSisTimestampe15190 install
	$(MAKE) -C detectors/HTHiRA install
	$(MAKE) -C detectors/HTNeutronWall install
	$(MAKE) -C detectors/HTVetoWall install
	$(MAKE) -C detectors/HTForwardArray install
	$(MAKE) -C detectors/HTMicroball install
	$(MAKE) -C detectors/HTTDCSpare install
	$(MAKE) -C detectors/HTIonChamber install
	$(MAKE) -C HTExperimentalSetup install
	$(MAKE) -C HTRawDataReader install
	$(MAKE) -C HTCalibration install	

distclean:
	$(MAKE) -C electronics distclean
	$(MAKE) -C RBExperiment distclean
	$(MAKE) -C logo distclean
	$(MAKE) -C HTRunInfo distclean
	$(MAKE) -C HTRootElectronics distclean
	$(MAKE) -C detectors/HTDetector distclean
	$(MAKE) -C detectors/HTSisTimestampe15190 distclean
	$(MAKE) -C detectors/HTHiRA distclean
	$(MAKE) -C detectors/HTNeutronWall distclean
	$(MAKE) -C detectors/HTVetoWall distclean
	$(MAKE) -C detectors/HTForwardArray distclean
	$(MAKE) -C detectors/HTMicroball distclean
	$(MAKE) -C detectors/HTTDCSpare distclean
	$(MAKE) -C HTExperimentalSetup distclean
	$(MAKE) -C HTRawDataReader distclean

	$(MAKE) -C FilterUnpacker  distclean
	$(MAKE) -C HTMapper  distclean
	$(MAKE) -C HTCalibration distclean

clean:
	$(MAKE) -C electronics  clean
	$(MAKE) -C RBExperiment clean
	$(MAKE) -C logo clean
	$(MAKE) -C HTRunInfo clean
	$(MAKE) -C HTRootElectronics clean
	$(MAKE) -C detectors/HTDetector clean
	$(MAKE) -C detectors/HTSisTimestampe15190 clean
	$(MAKE) -C detectors/HTHiRA clean
	$(MAKE) -C detectors/HTNeutronWall clean
	$(MAKE) -C detectors/HTVetoWall clean
	$(MAKE) -C detectors/HTForwardArray clean
	$(MAKE) -C detectors/HTMicroball clean
	$(MAKE) -C detectors/HTTDCSpare clean
	$(MAKE) -C detectors/HTIonChamber clean
	$(MAKE) -C HTExperimentalSetup clean
	$(MAKE) -C HTRawDataReader clean

	$(MAKE) -C FilterUnpacker  clean
	$(MAKE) -C HTMapper  clean
	$(MAKE) -C HTCalibration clean

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C electronics
	$(MAKE) -C RBExperiment
	$(MAKE) -C logo
	$(MAKE) -C HTRunInfo
	$(MAKE) -C HTRootElectronics
	$(MAKE) -C detectors/HTDetector
	$(MAKE) -C detectors/HTSisTimestampe15190
	$(MAKE) -C detectors/HTHiRA
	$(MAKE) -C detectors/HTNeutronWall
	$(MAKE) -C detectors/HTVetoWall
	$(MAKE) -C detectors/HTForwardArray
	$(MAKE) -C detectors/HTMicroball
	$(MAKE) -C detectors/HTTDCSpare	
	$(MAKE) -C HTExperimentalSetup
	$(MAKE) -C HTRawDataReader

	$(MAKE) -C FilterUnpacker
	$(MAKE) -C HTMapper  
	$(MAKE) -C HTCalibration 	
