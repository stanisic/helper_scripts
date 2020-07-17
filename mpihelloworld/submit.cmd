#!/bin/bash -l

#SBATCH --job-name=mpitest    # Job name
#SBATCH --output=jobname.%j.out # Stdout (%j expands to jobId)
#SBATCH --error=jobname.%j.err # Stderr (%j expands to jobId)
#SBATCH --ntasks=6     # Number of tasks(processes)
#SBATCH --nodes=2     # Number of nodes requested
#SBATCH --ntasks-per-node=3     # Tasks per node
#SBATCH --cpus-per-task=1     # Threads per task
#SBATCH --time=00:10:00   # walltime
#XBATCH --mem=56G   # memory per NODE
#SBATCH --partition=_specify_   # Partition

if [ x$SLURM_CPUS_PER_TASK == x ]; then
  export OMP_NUM_THREADS=1
else
  export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
fi

## RUN YOUR PROGRAM ##
srun ./mpi_hello_world
