#!/bin/sh -e

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)
WORK_DIR="$BASEDIR/.."
PLATFORM="$(uname -a | grep -i -o -e ubuntu -e debian | tr '[:lower:]' '[:upper:]')"

cd "$WORK_DIR"
if [ "$PLATFORM" == "UBUNTU" ]; then
    script/get-ubuntu-deps.sh
elif [ "$PLATFORM" == "DEBIAN" ]; then
    script/get-ubuntu-deps.sh
fi

cd "$WORK_DIR"
script/get-open-mpi.sh

cd "$WORK_DIR"
script/get-boost.sh
