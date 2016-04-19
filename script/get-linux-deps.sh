#!/bin/sh -e

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)
WORK_DIR="$BASEDIR/.."

cd "$WORK_DIR"
if [ "$(uname -a | grep Ubuntu)" != "" ]; then
    script/get-ubuntu-deps.sh
fi

cd "$WORK_DIR"
script/get-open-mpi.sh

cd "$WORK_DIR"
script/get-boost-mpi.sh
