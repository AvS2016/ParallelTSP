file(GLOB test_src *.cpp)

add_executable(testga ${test_src})
target_link_libraries(testga ${PROJ_LIBRARIES})