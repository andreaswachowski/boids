add_library(common OBJECT boid.cpp)

target_include_directories(common PUBLIC include)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(common PRIVATE --coverage)
  target_link_options(common PRIVATE --coverage)
endif()
