#!/usr/bin/env bash
#--- sbatch option ---#
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=5000
#SBATCH --job-name=4045-6
#SBATCH --output=/mnt/analysis/e15190/HiRAEVTUnpacker_summaries/slurm-%A_%a.out
module add intel

cd /projects/hira/Daniele/HiRAEVT
source /projects/hira/Daniele/HiRAEVT/bin/HiRAEVT.sh
eval '/projects/hira/Daniele/HiRAEVT/bin/HiRAEVTUnpacker.exe --source=file://'/mnt/misc/daqevents-ro/e15190_2/experiment/run4045/run-4045-06.evt' --sink=file:///dev/null'
