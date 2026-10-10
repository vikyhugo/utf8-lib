cmake_minimum_required(VERSION 3.0...4.4.4)
project("utf8-lib" C)

enable_testing()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library("utf8-lib" "${CMAKE_CURRENT_SOURCE_DIR}/src/utf8-lib.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/tests")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
