add_executable(cli_tests test_runner.cpp)

include(GoogleTest)

# Because common is an object library, there's no place to link gcov to it.
# Adding --coverage will pass "-lgcov" to the test executable
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(cli_tests PRIVATE --coverage)
  target_link_options(cli_tests PRIVATE --coverage)
endif()

target_link_libraries(cli_tests PRIVATE GTest::gtest_main cli common)
target_include_directories(cli_tests PRIVATE ${PROJECT_SOURCE_DIR}/src/cli)

gtest_discover_tests(cli_tests)
