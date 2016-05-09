set(EXEC_NAME simplega)
set(EXEC_LIBRARIES data json genetic ${Boost_PROGRAM_OPTIONS_LIBRARY})
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES})