add_executable(
        madbf

        "src/main.c"
)

target_link_libraries(madbf madvm madlib)
