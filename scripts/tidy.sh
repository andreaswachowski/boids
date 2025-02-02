#!/usr/bin/env bash

cd "$(dirname "$0")"/.. || exit 1

if [ "$(uname -s)" = "Darwin" ]; then
  # Macos native bash 3.2 does not support "echo -n"
  SH=/opt/homebrew/bin/bash
else
  SH="sh"
fi

pwd
echo
echo -n "Running clang-tidy "

find . -type f \( -name "*\.cpp" -o -name "*\.h" \) ! -path "./Debug/*" ! -path "./Release/*" ! -path "./venv/*" |
  xargs -I {} $SH -c "clang-tidy {}; echo -n '.'"
