#!/usr/bin/env bash
#PBS -m a
#PBS -l nodes=1:ppn=1,mem=2gb,walltime=00:20:00
#PBS -N Unpacking_/mnt/misc/daqevents-ro/e15190/experiment/run2815/run-2815-00.evt
#PBS -j oe
#PBS -S /bin/bash
module swap GNU Intel/13.0.1.117
 
/projects/e15190/ribbitMerged/bin/UnpackerFilter --source=file://'/mnt/misc/daqevents-ro/e15190/experiment/run2815/run-2815-00.evt' --sink=file:///dev/null
