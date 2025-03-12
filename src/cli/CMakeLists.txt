include(cmake/Dependencies.cmake)

add_library(cli OBJECT runner.cpp ncurses_output.cpp)

target_include_directories(cli PRIVATE ${CURSES_INCLUDE_PATH})
target_include_directories(cli PUBLIC .)
target_link_libraries(cli PRIVATE ${CURSES_LIBRARY} common spdlog::spdlog
                                  CLI11::CLI11)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(cli PRIVATE --coverage)
  target_link_options(cli PRIVATE --coverage)
endif()
