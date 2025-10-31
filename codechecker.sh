#!/bin/bash

set -e
set -u

REPORT_DIR="reports"
REPORT_HTML_DIR="reports_html"

print_usage() {
  echo "Usage: $0 [Debug|Release]"
  exit 1
}

prepare_build_dir() {
  if [[ -d "$BUILD_DIR" ]]; then
    echo "Removing existing build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
  else
    echo "Creating build directory: $BUILD_DIR"
  fi
  mkdir -p "$BUILD_DIR"
}

configure_cmake() {
  local CMAKE_BUILD_TYPE="$1"
  echo "Configuring CMake with build_type: $CMAKE_BUILD_TYPE"
  cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"
}

run_codechecker_analysis() {
  echo "Running CodeChecker analysis"
  cd "$BUILD_DIR"
  CodeChecker log --build "make -j24" --output ./compile_commands.json
  CodeChecker analyze -j24 ./compile_commands.json --enable sensitive --output "$REPORT_DIR"
  CodeChecker parse --export html --output "$REPORT_HTML_DIR" "$REPORT_DIR"
}

main() {
  if [[ $# -ne 1 ]]; then
    print_usage
  fi

  local CMAKE_BUILD_TYPE="$1"

  case "$CMAKE_BUILD_TYPE" in
    Debug|Release) ;;
    *) echo "Invalid build type: $CMAKE_BUILD_TYPE"; print_usage ;;
  esac

  local BUILD_DIR="build_${CMAKE_BUILD_TYPE,,}"

  prepare_build_dir "$BUILD_DIR"
  configure_cmake "$BUILD_DIR"
  run_codechecker_analysis "$BUILD_DIR"

  echo "Finished!"
}

main "$@"
