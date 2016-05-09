set(EXEC_NAME dirty)
#set(EXEC_LIBRARIES "")
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES} ${Boost_MPI_LIBRARY} ${MPI_CXX_LIBRARIES})
#${Boost_PROGRAM_OPTIONS_LIBRARY}
#${BOOST_SERIALIZATION_LIBRARY}