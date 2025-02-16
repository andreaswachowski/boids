add_executable(boid-cli cli/main.cpp)

add_subdirectory(common)
add_subdirectory(cli)

target_include_directories(boid-cli PRIVATE cli/include)
target_link_libraries(boid-cli PRIVATE ${CURSES_LIBRARY} common cli)
