foreach(lib ${PROJ_LIBRARIES})
    file(GLOB lib_src ${lib}/*.cpp)
    add_library(${lib} ${lib_src})
endforeach(lib ${PROJ_LIBRARIES})

foreach(exec ${PROJ_EXEC})
    add_subdirectory(${exec})
endforeach(exec ${PROJ_EXEC})
