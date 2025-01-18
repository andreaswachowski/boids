add_executable(tests test_main.cpp)
target_link_libraries(tests PRIVATE gtest_main boid_library spdlog::spdlog)
include(GoogleTest)
gtest_discover_tests(tests)
