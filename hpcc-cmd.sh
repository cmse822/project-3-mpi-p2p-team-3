#!/bin/bash --login
########## SBATCH Lines for Resource Request ##########

#SBATCH --time=13:00:00             # limit of wall clock time - how long the job will run (same as -t)
#SBATCH --nodes=1                 # number of different nodes - could be an exact number or a range of nodes (same as -N)
#SBATCH --ntasks=1                  # number of tasks - how many tasks (nodes) that you require (same as -n)
#SBATCH --cpus-per-task=4         # number of CPUs (or cores) per task (same as -c)
#SBATCH --mem-per-cpu=120G            # memory required per allocated CPU (or core) - amount of memory (in bytes)
#SBATCH --job-name prodigy      # you can give your job a name for easier identification (same as -J)
#SBATCH --gres=gpu:a100:1

########## Command Lines for Job Running ##########

module purge
module load GCC/6.4.0-2.28 OpenMPI  ### load necessary modules.
ssh dev-amd20-v100 


