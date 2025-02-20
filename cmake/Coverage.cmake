function(AddCoverage target)
  find_program(LCOV_PATH lcov REQUIRED)
  find_program(GENHTML_PATH genhtml REQUIRED)

  get_target_property(GTEST_INCLUDE_DIR GTest::gtest
                      INTERFACE_INCLUDE_DIRECTORIES)
  if(NOT GTEST_INCLUDE_DIR)
    message(FATAL_ERROR "Failed to get GoogleTest include directory")
  endif()

  add_custom_target(
    coverage
    COMMENT "Running coverage for ${target}..."
    COMMAND ${LCOV_PATH} -d . --zerocounters
    COMMAND $<TARGET_FILE:${target}>
    COMMAND
      ${LCOV_PATH} -d . --ignore-errors unsupported --exclude
      ${GTEST_INCLUDE_DIR} --exclude ${CMAKE_SOURCE_DIR}/tests --gcov-tool
      llvm-cov,gcov --capture -o coverage.info
    COMMAND ${LCOV_PATH} -d . -r coverage.info '/usr/include/*' -o filtered.info
    COMMAND ${GENHTML_PATH} -o coverage filtered.info
    COMMAND rm -rf coverage.info filtered.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
