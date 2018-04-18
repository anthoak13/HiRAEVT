#For questions, talk to Juan Manfredi

module unload root
module load root/gnu/5.34.32

#Set ROOT version to 5.34.32
export ROOTSYS='/mnt/misc/sw/x86_64/Debian/8/root/gnu/5.34.32'

export LD_LIBRARY_PATH=$ROOTSYS/lib/root:$LD_LIBRARY_PATH:./

#Set environmental variables for ribbit
export RIBbitSRC=/projects/hira/Daniele/RIBbit2-dev
export RIBbitLIB=/projects/hira/Daniele/RIBbit2-dev/lib
export RIBbitBIN=/projects/hira/Daniele/RIBbit2-dev/bin
export RIBbitDAQROOT=/usr/opt/nscldaq/current
export DAQROOT=/usr/opt/nscldaq/current


export LD_LIBRARY_PATH=/usr/opt/nscldaq/current/lib:$RIBbitLIB:$LD_LIBRARY_PATH
export PATH=$RIBbitBIN:$PATH

#Set the compiler
#if [ "$(hostname)" = "seaside" ]
#then export ROOTCLINGORCINT='rootcint'
#else export ROOTCLINGORCINT='rootcling'
#fi

export ROOTCLINGORCINT='rootcint'
