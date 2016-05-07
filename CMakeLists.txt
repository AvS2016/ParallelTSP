cmake_minimum_required(VERSION 2.8)

project(ParallelTSP)
    
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")
set(PROJ_LIBRARIES
    "json"
    "data"
    "genetic"
)
set(PROJ_EXEC
    "generator"
)

get_filename_component(BOOST_ROOT "./dep/boost" ABSOLUTE)
get_filename_component(MPI_C_COMPILER "./dep/openmpi/bin/mpicc" ABSOLUTE)
get_filename_component(MPI_CXX_COMPILER "./dep/openmpi/bin/mpicxx" ABSOLUTE)
set(Boost_NO_SYSTEM_PATHS "ON")

find_package(MPI REQUIRED)
find_package(Boost REQUIRED mpi program_options)

include_directories(
    ${MPI_CXX_INCLUDE_PATH}
    ${Boost_INCLUDE_DIRS}
    "src"
)

add_subdirectory("src")
