#For questions, talk to Juan Manfredi or Daniele Dell'Aquila (dellaqui@nscl.msu.edu)

ROOTVERSION=6.04.02

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
done < config/HiRAEVT.conf

export LD_LIBRARY_PATH=$ROOTSYS/lib/root:$LD_LIBRARY_PATH:./

#Set environmental variables for HiRAEVT
export HiRAEVTSRC=${HiRAEVTPath}
export HiRAEVTLIB=${HiRAEVTPath}lib
export HiRAEVTBIN=${HiRAEVTPath}bin
export HiRAEVTDAQROOT=/usr/opt/nscldaq/current
export DAQROOT=/usr/opt/nscldaq/current

export LD_LIBRARY_PATH=/usr/opt/nscldaq/current/lib:$HiRAEVTLIB:$LD_LIBRARY_PATH
export PATH=$HiRAEVTBIN:$PATH

#Making scripts executable
chmod +x ${HiRAEVTBIN}/HiRAEVT*

#Set the compiler
#if [ "$(hostname)" = "seaside" ]
#then export ROOTCLINGORCINT='rootcint'
#else export ROOTCLINGORCINT='rootcling'
#fi
