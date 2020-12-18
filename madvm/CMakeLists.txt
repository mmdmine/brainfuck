add_library(
        madvm

        "include/dictionary.h"
        "include/token.h"
        "include/opcode.h"
        "include/function.h"
        "include/program.h"
        "include/parser.h"
        "include/vm.h"

        "src/dictionary.c"
        "src/token.c"
        "src/opcode.c"
        "src/function.c"
        "src/program.c"
        "src/parser.c"
        "src/vm.c"
)
