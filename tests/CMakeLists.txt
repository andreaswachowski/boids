include(cmake/Dependencies.cmake)

include(Coverage)
addcoverage(common_tests cli_tests)

add_subdirectory(cli)
add_subdirectory(common)
