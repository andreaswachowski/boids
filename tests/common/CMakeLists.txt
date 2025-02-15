add_executable(common_tests test_boid.cpp)

include(GoogleTest)

target_link_libraries(common_tests PRIVATE GTest::gtest_main common)
target_include_directories(common_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/src/common/include)

gtest_discover_tests(common_tests)
