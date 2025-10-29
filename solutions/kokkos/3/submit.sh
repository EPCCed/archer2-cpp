#!/bin/bash
#
#PBS -N kokkos3
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
export OMP_NUM_THREADS=10

# Pick a random device as PBS on Cirrus not yet configured to control
# GPU visibility
r=$RANDOM; let "r %= 4";
export CUDA_VISIBLE_DEVICES=$r


for NROWS in 4 6 8 10 12 14 16; do
    echo "OpenMP version, OMP_NUM_THREADS=$OMP_NUM_THREADS"
    ./03_Exercise.OpenMP -N $NROWS
    echo "CudaUVM version"
    ./03_Exercise.Cuda -N $NROWS
done
