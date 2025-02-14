set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_OSX_DEPLOYMENT_TARGET 15.2)

# Export compile commands for tools like clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Parallel algorithms support for Clang 17+ and operating systems with libc++
# Primary source:
# https://libcxx.llvm.org/UserDocumentation.html#enabling-experimental-c-library-features
# Found via https://github.com/Stellarium/stellarium/pull/3902/files via
# https://github.com/Stellarium/stellarium/pull/3902 via
# https://github.com/llvm/llvm-project/issues/57898
if((${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 16.0)
   AND (APPLE OR ${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD"))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexperimental-library")
endif()
