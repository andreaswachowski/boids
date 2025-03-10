#!/usr/bin/env bash

# Based on https://github.com/gabime/spdlog/blob/v1.x/scripts/format.sh

cd "$(dirname "$0")"/.. || exit 1

if [ "$(uname -s)" = "Darwin" ]; then
  # Macos native bash 3.2 does not support "echo -n"
  SH=/opt/homebrew/bin/bash
else
  SH="sh"
fi

pwd

find_sources="find src tests -type f -name *\.h -o -name *\.cpp"
echo -n "Running dos2unix     "
$find_sources | xargs -I {} $SH -c "dos2unix '{}' 2>/dev/null; echo -n '.'"
echo
echo -n "Running clang-format "
$find_sources | xargs -I {} $SH -c "clang-format -i {}; echo -n '.'"

echo
echo -n "Running cmake-format "
find . -type f \( -name "CMakeLists.txt" -o -name "*\.cmake" \) ! -path "./Debug/*" ! -path "./Release/*" ! -path "./venv/*" |
  xargs -I {} $SH -c "cmake-format -i {}; echo -n '.'"
echo
