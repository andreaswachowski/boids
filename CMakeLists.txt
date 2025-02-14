cmake_minimum_required(VERSION 3.21)

project(BoidSimulation LANGUAGES CXX)

include(cmake/Config.cmake)
include(cmake/Dependencies.cmake)

add_executable(boid_simulation main.cpp)

add_subdirectory(src)

target_include_directories(boid_simulation PRIVATE ${CURSES_INCLUDE_PATH})
target_link_libraries(boid_simulation PRIVATE ${CURSES_LIBRARY} boids
                                              spdlog::spdlog CLI11::CLI11)

option(ENABLE_TESTING "Enable testing" ON)
if(ENABLE_TESTING)
  enable_testing()

  add_subdirectory(tests)
endif()
