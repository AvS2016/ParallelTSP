#!/bin/bash -e

BOOST_URL="http://downloads.sourceforge.net/project/boost/boost/1.60.0/boost_1_60_0.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.60.0%2F&ts=1461052894&use_mirror=tenet"
BOOST_ARCH="boost_1_60_0.tar.gz"
BOOST_DIR="boost_1_60_0"

mkdir -p dep
cd dep

export BOOST_INSTALL_DIR="$(pwd)/boost"

# install boost MPI
wget "$BOOST_URL" -O "$BOOST_ARCH"
tar xzf "$BOOST_ARCH"
rm -f "$BOOST_ARCH"
cd "$BOOST_DIR"
mkdir -p build
./bootstrap.sh
if [ "$(cat 'project-config.jam' | grep 'using mpi')" = "" ]; then
    echo "using mpi : $OPEN_MPI_DIR/bin/mpicc ;" >> "project-config.jam"
fi
./b2 --build-dir=build -j2 --prefix="$BOOST_INSTALL_DIR" install
