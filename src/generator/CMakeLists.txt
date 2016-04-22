set(EXEC_NAME graphgen)
set(EXEC_LIBRARIES json data)
file(GLOB src *.cpp)

add_executable(${EXEC_NAME} ${src})
target_link_libraries(${EXEC_NAME} ${EXEC_LIBRARIES})