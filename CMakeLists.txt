cmake_minimum_required(VERSION 3.10)

project(BoidSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(spdlog)

enable_testing()

add_executable(tests test_main.cpp boid.cpp)
target_link_libraries(tests PRIVATE gtest_main spdlog::spdlog)
include(GoogleTest)
gtest_discover_tests(tests)

add_executable(boid_simulation main.cpp boid.cpp)
include_directories(${CURSES_INCLUDE_PATH})
target_link_libraries(boid_simulation PRIVATE ${CURSES_LIBRARY} spdlog::spdlog)
