add_library(cli_tests OBJECT test_runner.cpp)

target_link_libraries(cli_tests PRIVATE GTest::gtest GTest::gmock cli common
                                        Microsoft.GSL::GSL)
