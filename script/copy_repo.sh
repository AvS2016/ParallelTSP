#!/bin/bash -e

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)

cd "$BASEDIR/.."

TSPDIR="$(basename "$(pwd)")"
TSPARCH="$TSPDIR.tar.gz"

cd ..

cptsp()
{
	host=$1
    echo "========================"
	echo "Copying TSP to $host ..."
	scp -r "$TSPARCH" $host:
    echo "Extracting tarball ..."
	ssh $host "tar xzf $TSPARCH"
}

echo "Creating tarball ..."
tar czf "$TSPARCH" "$TSPDIR"

cptsp pip02
cptsp pip03
cptsp pip04
cptsp pip05
cptsp pip06
cptsp pip08
cptsp pip09
cptsp pip10
cptsp pip11
