set(EXEC_NAME simplega)
set(EXEC_LIBRARIES genetic utils data json ${Boost_PROGRAM_OPTIONS_LIBRARY})
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES})