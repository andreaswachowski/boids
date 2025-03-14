include(FetchContent)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git
                     GIT_TAG v1.15.1 FIND_PACKAGE_ARGS)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(GSL GIT_REPOSITORY https://github.com/microsoft/GSL
                     GIT_TAG "v4.2.0" GIT_SHALLOW ON)
FetchContent_MakeAvailable(GSL)
