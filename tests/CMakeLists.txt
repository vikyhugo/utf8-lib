add_executable("test_nextCodePt" "${CMAKE_CURRENT_SOURCE_DIR}/src/test_nextCodePt.c")
add_test(NAME "test_nextCodePt" COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_nextCodePt" "${CMAKE_CURRENT_SOURCE_DIR}/data/test_nextCodePt/data.bin" "${CMAKE_CURRENT_SOURCE_DIR}/data/test_nextCodePt/expected.bin")
target_link_libraries("test_nextCodePt" "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/utf8-lib.a")
