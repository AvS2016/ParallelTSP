#!/bin/bash -e

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)
WORK_DIR="$BASEDIR/.."
PLATFORM="$(uname -a | grep -i -o -e ubuntu -e debian | tr '[:lower:]' '[:upper:]')"

dlfile()
{
    URL=$1
    FILE=$2
    type wget >/dev/null 2>&1
    if [ "$?" = "0" ]; then
        wget "$URL" -O "$FILE"
    else
        curl -o "$FILE" -L "$URL"
    fi
}

cd "$WORK_DIR"
if [ "$PLATFORM" = "UBUNTU" ]; then
    . script/get-ubuntu-deps.sh
elif [ "$PLATFORM" = "DEBIAN" ]; then
    . script/get-ubuntu-deps.sh
fi

cd "$WORK_DIR"
. script/get-open-mpi.sh

cd "$WORK_DIR"
. script/get-boost.sh
