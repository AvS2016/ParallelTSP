foreach(comp ${PROJ_COMP})
    file(GLOB comp_src ${comp}/*.cpp)
    add_library(${comp} ${comp_src})
endforeach(comp ${PROJ_COMP})