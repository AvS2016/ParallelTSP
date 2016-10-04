#!/bin/bash -e

TSPDIR="/Users/jmarkert/ParallelTSP"
#TSPDIR="/home/fabian/develop/ParallelTSP"
SINGLE_CMD="$TSPDIR/build/src/simplega/simplega -c graph/cfg.json -q"
MULTI_CMD="/$TSPDIR/dep/openmpi/bin/mpiexec -np COUNT $TSPDIR/build/src/simplega/simplega -c graph/cfg.json -n -q"
ALL_CMD="$TSPDIR/dep/openmpi/bin/mpiexec --hostfile $TSPDIR/hostfile.txt -map-by node -np COUNT $TSPDIR/build/src/simplega/simplega -c graph/cfg.json -n -q"
RUNS=100
DATADIR="$TSPDIR/data"

runtsp()
{
	NAME=$2
	COUNT=$3
	CMD="$(echo "$1" | sed -e "s|COUNT|$COUNT|g")"
	
	for i in $(seq 1 $RUNS); do
		STATFILE="$NAME"_$(printf "%03d" $i).json
		$CMD
		cp "statistics.json"  "$DATADIR/$STATFILE"
   	done
}

echo "Parallel TSP Data Aquisition"
echo "============================"

mkdir -p "$DATADIR"

while (( "$#" )); do
	echo "Run Scenario $1."
	case $1 in
	1)
		# Szenario 1, 1 process, single machine
	   	runtsp "$SINGLE_CMD" "01_Proc_01_Machines" 1
	   	;;
	2)
	   	# Szenario 2, 8 processes, single machine
	   	runtsp "$MULTI_CMD" "08_Proc_01_Machines" 8
	   	;;
	3)
	   	# Szenario 3, 40 processes, 10 machines
	   	runtsp "$ALL_CMD" "40_Proc_10_Machines" 40
	   	;;
	4)
	   	# Szenario 4, 80 processes, 10 machines
	   	runtsp "$ALL_CMD" "80_Proc_10_Machines" 80
	   	;;
	esac

	shift
done