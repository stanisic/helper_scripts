#!/bin/bash -l

#SBATCH --job-name=mpipinning    # Job name
#SBATCH --output=%j.out # Stdout (%j expands to jobId)
#SBATCH --error=%j.err # Stderr (%j expands to jobId)
#XBATCH --ntasks=6     # Number of tasks(processes)
#SBATCH --nodes=1     # Number of nodes requested
#SBATCH --ntasks-per-node=4     # Tasks per node
#SBATCH --cpus-per-task=1     # Threads per task
#SBATCH --time=00:10:00   # walltime
#XBATCH --mem=56G   # memory per NODE
#SBATCH --partition=_specify_   # Partition

if [ x$SLURM_CPUS_PER_TASK == x ]; then
  export OMP_NUM_THREADS=1
else
  export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
fi

# LOAD MODULES
module purge
module load GCC OpenMPI hwloc

## RUN YOUR PROGRAM ##
numactl -H

STRAT="default"
echo "#########"
echo "Strategy: $STRAT"
mpirun ./mpipinning

STRAT="core"
echo "#########"
echo "Strategy: $STRAT"
mpirun --report-bindings --bind-to core --map-by $STRAT ./mpipinning

STRAT="l2cache"
echo "#########"
echo "Strategy: $STRAT"
mpirun --report-bindings --bind-to core --map-by $STRAT ./mpipinning

STRAT="numa"
echo "#########"
echo "Strategy: $STRAT"
mpirun --report-bindings --bind-to core --map-by $STRAT ./mpipinning

STRAT="socket"
echo "#########"
echo "Strategy: $STRAT"
mpirun --report-bindings --bind-to core --map-by $STRAT ./mpipinning

