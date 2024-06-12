#include "surfer.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc > 3) {
        std::cerr << "Usage: sfml-surfer [html file] [OPTIONAL: css file]"
                  << std::endl;
    } else if (argc == 3) {
        Surfer::runFile(argv[1], argv[2]);
    } else if (argc == 2) {
        Surfer::runFile(argv[1]);
    } else {
        Surfer::runPrompt();
    }

    return 0;
}
