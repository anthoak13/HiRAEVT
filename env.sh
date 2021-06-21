#!/bin/bash

module purge
module load fairroot/18.6.3
module list

#module purge
#module load root
#module list

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export LD_LIBRARY_PATH=$DIR/build/install/lib:$LD_LIBRARY_PATH:/usr/opt/nscldaq/current/lib
export PATH=$DIR/build/install/bin:$PATH
