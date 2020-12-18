set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(
        madbf

        "src/main.c"
)

target_link_libraries(madbf madvm madlib)
