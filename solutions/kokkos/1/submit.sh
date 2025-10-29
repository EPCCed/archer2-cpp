#!/bin/bash
#
#PBS -N kokkos1
#PBS -q gpu-teach
#PBS -l select=1:ncpus=10:ngpus=1
#PBS -l walltime=0:01:00

# Budget: use either your default or the reservation
#PBS -A d171

# Load the required modules
module load gcc cuda kokkos

cd $PBS_O_WORKDIR

export OMP_PROC_BIND=spread
export OMP_PLACES=threads

for threads in 1 2 4 8; do
    export OMP_NUM_THREADS=$threads
    echo "OMP_NUM_THREADS=$OMP_NUM_THREADS"
    for NROWS in 4 6 8 10 12 14 16; do
	./01_Exercise.OpenMP -N $NROWS
    done
done


