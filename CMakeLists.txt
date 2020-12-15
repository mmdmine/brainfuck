# Mad Brainfuck Interpreter

cmake_minimum_required (VERSION 3.8)

project ("Brainfuck")

include(CTest)

include_directories(include)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
