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

## OpenMPI

Execute the following command to run on multiple machines
(Example for current dir="build")
``
```
cd <path-to-repo>
dep/openmpi/bin/mpirun --allow-run-as-root -np X --prefix <prefix> -hostfile <path-to-hostfile> build/src/dirtytesting/dirty
```

```-np X``` specifies how many processes should be started. OpenMPI takes care of assigning the processes to nodes in the network.

```--prefix``` specifies the path prefix for OpenMPI, which is usually ```<path-to-repo>/dep/openmpi```. mpiexec searches in that directory for the mpi libraries. Prefix can only be specified once and has to be the same for nodes in the system. Otherwise the OpenMPI path has to be set in the ```PATH``` environment variable.

```-hostfile``` specifies a file that states all nodes/hosts for the network.

A sample hostfile looks like this:
```
root@192.168.1.3 slots=2
root@192.168.1.4 slots=2
```
