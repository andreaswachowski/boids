add_library(common_tests OBJECT test_boid.cpp)

target_link_libraries(common_tests PRIVATE GTest::gtest common)
