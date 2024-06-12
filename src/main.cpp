#include "surfer.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: sfml-surfer [html file]" << std::endl;
    } else if (argc == 2) {
        Surfer::runFile(argv[1]);
    } else {
        Surfer::runPrompt();
    }

    return 0;
}
