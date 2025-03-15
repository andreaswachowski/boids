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
    # Get the currently used compiler
    execute_process(
      COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE COMPILER_VERSION
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(CMAKE_CXX_COMPILER MATCHES "/opt/homebrew/opt/llvm@")
      # If using Homebrew LLVM, set its include path
      string(REGEX MATCH "^[0-9]+" COMPILER_MAJOR_VERSION
                   "${CMAKE_CXX_COMPILER_VERSION}")
      set(SYSTEM_INCLUDE_PATH
          "/opt/homebrew/opt/llvm@${COMPILER_MAJOR_VERSION}/include")
    else()
      # Default to Xcode's SDK include path
      execute_process(
        COMMAND xcrun --sdk macosx --show-sdk-path
        OUTPUT_VARIABLE SYSTEM_INCLUDE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
      set(SYSTEM_INCLUDE_PATH "${SYSTEM_INCLUDE_PATH}/usr/include")
    endif()
  elseif(UNIX AND NOT APPLE)
    set(SYSTEM_INCLUDE_PATH "/usr/include")
  else()
    message(FATAL_ERROR "Unsupported platform for coverage collection")
  endif()

  # "unused" is required for /usr/include (i.e. what else, if anything, should I
  # use in the assignment of SYSTEM_INCLUDE_PATH above?) and for Macos, but only
  # in the CI-pipeline (I need the exclude locally)
  set(LCOV_ARGS
      --parallel
      --ignore-errors
      unsupported,unused,category,inconsistent
      --rc
      branch_coverage=1
      --rc
      derive_function_end_line=0
      --filter
      brace)
  set(COV_NAME coverage)
  set(LCOV_EXCLUDES
      --exclude
      include
      --exclude
      CLI
      --exclude
      ${SYSTEM_INCLUDE_PATH}
      --exclude
      ${GTEST_INCLUDE_DIR}
      --exclude
      ${CMAKE_SOURCE_DIR}/tests)

  # Parts from
  # https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
  add_custom_target(
    coverage
    COMMENT "Running coverage for ${target}..."
    # Cleanup lcov
    COMMAND ${LCOV_PATH} ${LCOV_ARGS} -d . --zerocounters
    # Create baseline to make sure untouched files show up in the report
    COMMAND
      ${LCOV_PATH} ${LCOV_ARGS} ${LCOV_EXCLUDES} --erase-functions
      __cxx_global_var_init -d . --gcov-tool ${GCOV_PATH} -c -i -o
      ${COV_NAME}.base
    # Run tests
    COMMAND $<TARGET_FILE:${target}>
    # Capturing lcov counters and generating report
    # "filter brace" to avoid closing braces to count on coverage. This
    # happened with clang and not GNU, thus having incomparable results.
    # https://github.com/linux-test-project/lcov/issues/129
    # https://github.com/linux-test-project/lcov/issues/160#issuecomment-1543738264
    COMMAND
      ${LCOV_PATH} ${LCOV_ARGS} ${LCOV_EXCLUDES} --erase-functions
      __cxx_global_var_init -d . --gcov-tool ${GCOV_PATH} --capture -o
      ${COV_NAME}.capture
    # Add baseline counters
    COMMAND
      ${LCOV_PATH} ${LCOV_ARGS} ${LCOV_EXCLUDES} --gcov-tool ${GCOV_PATH} -a
      ${COV_NAME}.base -a ${COV_NAME}.capture --output-file ${COV_NAME}.total
    # filter collected data to final coverage report
    COMMAND ${LCOV_PATH} ${LCOV_ARGS} ${LCOV_EXCLUDES} -d . -r ${COV_NAME}.total
            -o ${COV_NAME}.info
    # Generate HTML output
    COMMAND ${GENHTML_PATH} ${LCOV_ARGS} --erase-functions __cxx_global_var_init
            -o coverage ${COV_NAME}.info
    COMMAND rm -rf ${COV_NAME}.capture ${COV_NAME}.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
