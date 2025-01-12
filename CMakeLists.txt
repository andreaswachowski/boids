# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(BoidSimulation LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(boid_simulation main.cpp)

# Manually specify ncurses location if installed via Homebrew
set(CURSES_INCLUDE_PATH /opt/homebrew/opt/ncurses/include)
set(CURSES_LIBRARY /opt/homebrew/opt/ncurses/lib/libncurses.dylib)

# Link the ncurses library
# find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_PATH})
target_link_libraries(boid_simulation PRIVATE ${CURSES_LIBRARY})
