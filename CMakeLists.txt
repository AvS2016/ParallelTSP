cmake_minimum_required(VERSION 2.8)

project(ParallelTSP)
    
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")
set(PROJ_LIBRARIES
    "data"
    "json"
    "genetic"
    "utils"
)
set(PROJ_EXEC
    "generator"
    "converter"
    "simplega"
)

get_filename_component(BOOST_ROOT "./dep/boost" ABSOLUTE)
get_filename_component(MPI_C_COMPILER "./dep/openmpi/bin/mpicc" ABSOLUTE)
get_filename_component(MPI_CXX_COMPILER "./dep/openmpi/bin/mpicxx" ABSOLUTE)
get_filename_component(CATCH_ROOT "./dep/catch" ABSOLUTE)
set(Boost_NO_SYSTEM_PATHS "ON")

get_filename_component(MODULES_PATH "./cmake-modules" ABSOLUTE) 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULES_PATH})

find_package(MPI REQUIRED)
find_package(Boost REQUIRED mpi program_options)
find_package(Catch REQUIRED)

include_directories(
    ${MPI_CXX_INCLUDE_PATH}
    ${Boost_INCLUDE_DIRS}
    ${CATCH_INCLUDE_DIR}
    "src"
)

add_subdirectory("src")
add_subdirectory("test")