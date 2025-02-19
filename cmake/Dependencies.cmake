include(FetchContent)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git
                     GIT_TAG v1.15.1 FIND_PACKAGE_ARGS)
FetchContent_MakeAvailable(spdlog)
