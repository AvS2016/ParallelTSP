#!/bin/sh

COUNT=$1

/Users/jmarkert/ParallelTSP/dep/openmpi/bin/mpiexec --hostfile /Users/jmarkert/ParallelTSP/hostfile.txt -map-by node -np $COUNT /Users/jmarkert/ParallelTSP/build/src/simplega/simplega -c graph/cfg.json -n -q
