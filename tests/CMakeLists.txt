set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_executable(tokenizer tokenizer.c)
target_link_libraries(tokenizer libmadbf)

add_executable(parser parser.c)
target_link_libraries(parser libmadbf)

add_test(tokenizer tokenizer)
add_test(parser parser)
