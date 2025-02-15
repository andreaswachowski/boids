cmake_minimum_required(VERSION 3.21)

project(BoidSimulation LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "Non in-source builds please")
endif()

include(cmake/Config.cmake)
include(cmake/Dependencies.cmake)

add_executable(boid_simulation main.cpp)

add_subdirectory(src bin)

target_link_libraries(boid_simulation PRIVATE cli common)

option(ENABLE_TESTING "Enable testing" ON)
if(ENABLE_TESTING)
  enable_testing()

  add_subdirectory(tests)
endif()
