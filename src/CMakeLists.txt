set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_library(
        libmadbf
        "dictionary.c"
        "token.c"
        "parser.c"
        "vm.c"
)

add_library(
        libstdmad
        "madlib.c"
)

target_link_libraries(libstdmad libmadbf)

add_executable(
        madbf
        "Brainfuck.c"
)

target_link_libraries(madbf libmadbf libstdmad)
