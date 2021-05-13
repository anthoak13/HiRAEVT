#!/bin/bash

module purge
module load fairroot/18.00
module list

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export LD_LIBRARY_PATH=$DIR/build/lib:$LD_LIBRARY_PATH
export PATH=$DIR/build/bin:$PATH
