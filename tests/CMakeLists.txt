include(cmake/Dependencies.cmake)

add_executable(boids_tests)

include(GoogleTest)

include(Coverage)
addcoverage(boids_tests)

# Adding --coverage will pass "-lgcov" to the test executable
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(boids_tests PRIVATE --coverage)
  target_link_options(boids_tests PRIVATE --coverage)
endif()

add_subdirectory(cli)
add_subdirectory(common)

target_link_libraries(
  boids_tests
  PRIVATE GTest::gtest_main
          GTest::gmock_main
          cli_tests
          common_tests
          cli
          common
          Microsoft.GSL::GSL)
target_include_directories(boids_tests PRIVATE ${PROJECT_SOURCE_DIR}/src/common
                                               ${PROJECT_SOURCE_DIR}/src/cli)

gtest_discover_tests(boids_tests)
