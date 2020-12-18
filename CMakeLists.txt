# Mad Brainfuck Interpreter

cmake_minimum_required (VERSION 3.8)

project ("Brainfuck")

include(CTest)

include_directories(
        "madvm/include"
        "madlib/include"
)

add_subdirectory(madvm)
add_subdirectory(madlib)
add_subdirectory(madbf)

enable_testing()
add_subdirectory(tests)
