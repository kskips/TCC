include_directories(${PROJECT_SOURCE_DIR}/inc/)
include_directories(${PROJECT_SOURCE_DIR}/inc/clusters/)
include_directories(${PROJECT_SOURCE_DIR}/extern/iniparser/inc/)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(tcc2 ${SOURCES})
target_link_libraries(tcc2 iniparser)
target_link_libraries(tcc2 m)

install(TARGETS tcc2 DESTINATION ${CMAKE_INSTALL_PREFIX})
