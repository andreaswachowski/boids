function(AddCoverage target)
  find_program(LCOV_PATH lcov REQUIRED)
  find_program(GENHTML_PATH genhtml REQUIRED)

  get_target_property(GTEST_INCLUDE_DIR GTest::gtest
                      INTERFACE_INCLUDE_DIRECTORIES)
  if(NOT GTEST_INCLUDE_DIR)
    message(FATAL_ERROR "Failed to get GoogleTest include directory")
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    find_program(GCOV_PATH gcov REQUIRED)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(GCOV_PATH ${CMAKE_SOURCE_DIR}/cmake/gcov-llvm-wrapper.sh)
  else()
    message(
      FATAL_ERROR "Unsupported compiler for coverage: ${CMAKE_CXX_COMPILER_ID}")
  endif()

  if(APPLE)
    execute_process(
      COMMAND xcrun --sdk macosx --show-sdk-path
      OUTPUT_VARIABLE SYSTEM_INCLUDE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(SYSTEM_INCLUDE_PATH "${SYSTEM_INCLUDE_PATH}/usr/include")
  elseif(UNIX AND NOT APPLE)
    set(SYSTEM_INCLUDE_PATH "/usr/include")
  else()
    message(FATAL_ERROR "Unsupported platform for coverage collection")
  endif()

  add_custom_target(
    coverage
    COMMENT "Running coverage for ${target}..."
    COMMAND ${LCOV_PATH} -d . --zerocounters
    COMMAND $<TARGET_FILE:${target}>
    COMMAND
      ${LCOV_PATH} -d . --ignore-errors unsupported,unused --exclude
      ${SYSTEM_INCLUDE_PATH} --exclude ${GTEST_INCLUDE_DIR} --exclude
      ${CMAKE_SOURCE_DIR}/tests --gcov-tool ${GCOV_PATH} --capture -o
      coverage.info
    # COMMAND find . -name '*.gcda' -o -name '*.gcno' -name '*.gcov'
    # COMMAND ${GENHTML_PATH} --version
    # COMMAND ${LCOV_PATH} --version
    COMMAND ${LCOV_PATH} -d . -r coverage.info -o filtered.info
    COMMAND ${GENHTML_PATH} --ignore-errors category,category -o coverage
            filtered.info
    COMMAND rm -rf coverage.info filtered.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
