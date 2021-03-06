#!/bin/bash -e

MPI_URL="https://www.open-mpi.org/software/ompi/v1.10/downloads/openmpi-1.10.2.tar.gz"
MPI_ARCH="openmpi-1.10.2.tar.gz"
MPI_DIR="openmpi-1.10.2"

if [ "$THREADS" = "" ]; then
    THREADS="2"
fi

mkdir -p dep
cd dep

export OPEN_MPI_DIR="$(pwd)/openmpi"

if [ -d "$OPEN_MPI_DIR" ]; then
    echo "OpenMPI already installed."
    return
fi

# install open MPI
dlfile "$MPI_URL" "$MPI_ARCH"
tar xzf "$MPI_ARCH"
rm -f "$MPI_ARCH"
cd "$MPI_DIR"

./configure --prefix="$OPEN_MPI_DIR"
make -j $THREADS install
