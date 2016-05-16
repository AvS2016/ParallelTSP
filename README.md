# ParallelTSP ![Build](https://travis-ci.org/AvS2016/ParallelTSP.svg?branch=master)

This is a parallelised genetic algorithm to solve the TSP across multiple machines.

## Build

To compile and install the dependencies of this project run

```
script/get-linux-deps.sh
```

This should download and compile

* OpenMPI 1.10-2
* Boost.MPI 1.60.0

On Ubuntu the script also downloads all dependencies to compile the libraries mentioned above.

Now you can build the project by running

```
cd <path-to-repo>
mkdir build
cd build
cmake ..
make
```

Execute the following command to run on multiple machines
(Example for current dir="build")
```
../dep/openmpi/bin/mpirun -H <host1>,<host2>,... <path to executable>
```
