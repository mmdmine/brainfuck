set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
add_library(
        madlib

        "include/madlib.h"

        "src/madlib.c"
)

target_link_libraries(madlib madvm)
