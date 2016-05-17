#!/bin/bash -e

MPI_URL="https://www.open-mpi.org/software/ompi/v1.10/downloads/openmpi-1.10.2.tar.gz"
MPI_ARCH="openmpi-1.10.2.tar.gz"
MPI_DIR="openmpi-1.10.2"

mkdir -p dep
cd dep

export OPEN_MPI_DIR="$(pwd)/openmpi"

# install open MPI
dlfile "$MPI_URL" "$MPI_ARCH"
tar xzf "$MPI_ARCH"
rm -f "$MPI_ARCH"
cd "$MPI_DIR"

./configure --prefix="$OPEN_MPI_DIR"
make -j4 install
