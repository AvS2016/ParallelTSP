set(EXEC_NAME simplega)
set(EXEC_LIBRARIES
    genetic 
    utils
    data
    json
    net
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_MPI_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${MPI_CXX_LIBRARIES}
)
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES})