#For questions, talk to Juan Manfredi or Daniele Dell'Aquila (dellaqui@nscl.msu.edu)

ROOTVERSION=6.04.02

#Set ROOT version to $ROOTVERSION ################################
# WARNING: the program works with ROOTVERSION>=6
module unload root
module load root/gnu/${ROOTVERSION}
source "/mnt/misc/sw/x86_64/Debian/8/root/gnu/${ROOTVERSION}/bin/thisroot.sh"
export ROOTCLINGORCINT='rootcling'
##################################################################

#determining RIBbit2 path from config/RIBbit2.conf
while IFS= read -r line;do
    fields=($(printf "%s" "$line"|cut --output-delimiter=' ' -f1-))
    if [ ${fields[1]} ] && [ ${fields[1]} = "RIBBIT2_DIR" ] ; then
      Ribbit2Path=$(echo ${fields[2]} | sed 's/[\"]//g')
    fi
done < config/RIBbit2.conf

export LD_LIBRARY_PATH=$ROOTSYS/lib/root:$LD_LIBRARY_PATH:./

#Set environmental variables for ribbit
export RIBbitSRC=${Ribbit2Path}
export RIBbitLIB=${Ribbit2Path}/lib
export RIBbitBIN=${Ribbit2Path}/bin
export RIBbitDAQROOT=/usr/opt/nscldaq/current
export DAQROOT=/usr/opt/nscldaq/current

export LD_LIBRARY_PATH=/usr/opt/nscldaq/current/lib:$RIBbitLIB:$LD_LIBRARY_PATH
export PATH=$RIBbitBIN:$PATH

#Set the compiler
#if [ "$(hostname)" = "seaside" ]
#then export ROOTCLINGORCINT='rootcint'
#else export ROOTCLINGORCINT='rootcling'
#fi
