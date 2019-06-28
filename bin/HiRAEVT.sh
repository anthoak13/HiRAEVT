#For questions, talk to Juan Manfredi or Daniele Dell'Aquila (dellaqui@nscl.msu.edu)

#Set the root version
ROOTVERSION=6.04.02

#Set the path of HiRAEVT config file
export HiRAEVTCONFIG=config/HiRAEVT.conf

#Set ROOT version to $ROOTVERSION ################################
# WARNING: the program works with ROOTVERSION>=6
module unload root
module load root/gnu/${ROOTVERSION}
source "/mnt/misc/sw/x86_64/Debian/8/root/gnu/${ROOTVERSION}/bin/thisroot.sh"
export ROOTCLINGORCINT='rootcling'
##################################################################

#determining HiRAEVT path from config/HiRAEVT.conf
while IFS= read -r line;do
    fields=($(printf "%s" "$line"|cut --output-delimiter=' ' -f1-))
    if [ ${fields[1]} ] && [ ${fields[1]} = "HiRAEVT_DIR" ] ; then
      HiRAEVTPath=$(echo ${fields[2]} | sed 's/[\"]//g')
    fi
done < $HiRAEVTCONFIG

export LD_LIBRARY_PATH=$ROOTSYS/lib/root:$LD_LIBRARY_PATH:./

#Set environmental variables for HiRAEVT
export HiRAEVTSRC=${HiRAEVTPath}
export HiRAEVTLIB=${HiRAEVTPath}/lib
export HiRAEVTBIN=${HiRAEVTPath}/bin
export HiRAEVTDAQROOT=/usr/opt/nscldaq/current
export DAQROOT=/usr/opt/nscldaq/current

export LD_LIBRARY_PATH=/usr/opt/nscldaq/current/lib:$HiRAEVTLIB:$LD_LIBRARY_PATH
export PATH=$HiRAEVTBIN:$PATH

#Making scripts executable
chmod +x ${HiRAEVTBIN}/HiRAEVT*

#Setting executable file name
case $HOSTNAME in
  (ember) 
    export NAMEHIRAEVTUNPACKEREXECUTABLE='HiRAEVTUnpackerEmber.exe'
    export NAMEHIRAEVTMAPPEREXECUTABLE='HiRAEVTMapperEmber.exe'
  ;;
  (seaside)
    export NAMEHIRAEVTUNPACKEREXECUTABLE='HiRAEVTUnpackerSeaside.exe'
    export NAMEHIRAEVTMAPPEREXECUTABLE='HiRAEVTMapperSeaside.exe'
  ;;
  (*)
    export NAMEHIRAEVTUNPACKEREXECUTABLE='HiRAEVTUnpacker.exe'
    export NAMEHIRAEVTMAPPEREXECUTABLE='HiRAEVTMapper.exe'  
  ;;
esac
