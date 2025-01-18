cmake_minimum_required(VERSION 3.10)

project(BoidSimulation LANGUAGES CXX)

include(cmake/Config.cmake)
include(cmake/Dependencies.cmake)

add_library(boid_library src/boid.cpp)

add_executable(boid_simulation src/main.cpp)
target_include_directories(boid_simulation PRIVATE ${CURSES_INCLUDE_PATH})
target_link_libraries(boid_simulation PRIVATE ${CURSES_LIBRARY} boid_library
                                              spdlog::spdlog)

option(ENABLE_TESTING "Enable testing" ON)
if(ENABLE_TESTING)
  enable_testing()

  add_subdirectory(tests)
endif()
