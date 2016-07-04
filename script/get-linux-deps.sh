#!/bin/bash -e

CURRDIR=$PWD
BASEDIR=$(cd "$(dirname "$0")"; pwd)
WORK_DIR="$BASEDIR/.."
PLATFORM="$(uname -a | grep -i -o -e ubuntu -e debian | tr '[:lower:]' '[:upper:]')"
export THREADS="$1"

dlfile()
{
    URL=$1
    FILE=$2
    set +e
    type wget >/dev/null 2>&1
    RET=$?
    set -e
    if [ "$RET" = "0" ]; then
        wget --no-check-certificate "$URL" -O "$FILE"
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

cd "$WORK_DIR"
. script/get-catch.sh
