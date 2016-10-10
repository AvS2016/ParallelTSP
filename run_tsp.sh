#!/bin/bash -e

TSPDIR="/Users/jmarkert/ParallelTSP"
#TSPDIR="/home/fabian/develop/ParallelTSP"
SINGLE_CMD="$TSPDIR/build/src/simplega/simplega -c graph/cfg.json -q -p POP"
MULTI_CMD="/$TSPDIR/dep/openmpi/bin/mpiexec -np COUNT $TSPDIR/build/src/simplega/simplega -c graph/cfg.json -n -q -p POP"
ALL_CMD="$TSPDIR/dep/openmpi/bin/mpiexec --hostfile $TSPDIR/hostfile.txt -map-by node -np COUNT $TSPDIR/build/src/simplega/simplega -c graph/cfg.json -n -q -p POP"
RUNS=1
DATADIR="$TSPDIR/data"

POP_TOTAL=50000
POP_01=$POP_TOTAL
POP_08=$(($POP_TOTAL / 8))
POP_40=$(($POP_TOTAL / 40))
POP_80=$(($POP_TOTAL / 80))

runtsp()
{
	NAME=$2
	COUNT=$3
    POP=$4
	CMD="$(echo "$1" | sed -e "s|COUNT|$COUNT|g" | sed -e "s|POP|$POP|g")"
	
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
	   	runtsp "$SINGLE_CMD" "01_Proc_01_Machines" 1 $POP_01
	   	;;
	2)
	   	# Szenario 2, 8 processes, single machine
	   	runtsp "$MULTI_CMD" "08_Proc_01_Machines" 8 $POP_08
	   	;;
	3)
	   	# Szenario 3, 40 processes, 10 machines
	   	runtsp "$ALL_CMD" "40_Proc_10_Machines" 40 $POP_40
	   	;;
	4)
	   	# Szenario 4, 80 processes, 10 machines
	   	runtsp "$ALL_CMD" "80_Proc_10_Machines" 80 $POP_80
	   	;;
	esac

	shift
done
