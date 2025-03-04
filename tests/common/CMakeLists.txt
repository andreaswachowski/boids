add_executable(common_tests test_boid.cpp)

include(Coverage)
addcoverage(common_tests)

include(GoogleTest)

# Because common is an object library, there's no place to link gcov to it.
# Adding --coverage will pass "-lgcov" to the test executable
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(common_tests PRIVATE --coverage)
  target_link_options(common_tests PRIVATE --coverage)
endif()

target_link_libraries(common_tests PRIVATE GTest::gtest_main common)
target_include_directories(common_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/src/common/include)

gtest_discover_tests(common_tests)
