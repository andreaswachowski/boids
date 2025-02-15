include(cmake/Dependencies.cmake)

add_library(cli OBJECT run.cpp)

target_include_directories(cli PRIVATE ${CURSES_INCLUDE_PATH})
target_include_directories(cli PUBLIC .)
target_link_libraries(cli PRIVATE ${CURSES_LIBRARY} common spdlog::spdlog
                                  CLI11::CLI11)
