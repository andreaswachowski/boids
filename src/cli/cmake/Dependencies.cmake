set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

include(FetchContent)
FetchContent_Declare(cli11 GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
                     GIT_TAG v2.4.2)
FetchContent_MakeAvailable(cli11)
