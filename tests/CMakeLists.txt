add_executable(tests test_main.cpp test_boid.cpp)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(tests PRIVATE gtest_main boids spdlog::spdlog)

include(GoogleTest)
gtest_discover_tests(tests)
