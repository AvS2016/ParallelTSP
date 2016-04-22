set(EXEC_NAME graphgen)
set(EXEC_LIBRARIES data json)
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})