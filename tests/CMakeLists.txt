set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/tests)
set(CTEST_BINARY_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_executable(dictionary "src/dictionary.c")
target_link_libraries(dictionary madvm)
add_test(dictionary dictionary)

add_executable(token "src/token.c")
target_link_libraries(token madvm)
add_test(token token)

add_executable(opcode "src/opcode.c")
target_link_libraries(opcode madvm)
add_test(opcode opcode)

add_executable(function "src/function.c")
target_link_libraries(function madvm)
add_test(function function)

add_executable(program "src/program.c")
target_link_libraries(program madvm)
add_test(program program)

add_executable(parser "src/parser.c")
target_link_libraries(parser madvm)
add_test(parser parser)

add_executable(vm "src/vm.c")
target_link_libraries(vm madvm)
add_test(vm vm)
