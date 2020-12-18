set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_executable(tokenizer_test src/tokenizer.c)
target_link_libraries(tokenizer_test madvm)

add_executable(parser_test src/parser.c)
target_link_libraries(parser_test madvm)

add_executable(vm_test src/vm.c)
target_link_libraries(vm_test madvm)

add_test(tokenizer tokenizer_test)
add_test(parser parser_test)
add_test(vm vm_test)
