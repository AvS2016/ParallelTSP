set(EXEC_NAME dirty)
set(EXEC_LIBRARIES
    ${Boost_MPI_LIBRARY}
    ${Boost_SERIALIZATION_LIBRARY}
    ${MPI_CXX_LIBRARIES}
)
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES})
