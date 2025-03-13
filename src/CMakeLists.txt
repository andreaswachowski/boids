add_executable(boid-cli main.cpp)

add_subdirectory(common)
add_subdirectory(cli)

target_link_libraries(boid-cli PRIVATE common cli)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(boid-cli PRIVATE --coverage)
  target_link_options(boid-cli PUBLIC --coverage)
  add_custom_command(
    TARGET boid-cli PRE_BUILD COMMAND find ${CMAKE_BINARY_DIR} -type f -name
                                      '*.gcda' -exec rm {} +)
endif()
