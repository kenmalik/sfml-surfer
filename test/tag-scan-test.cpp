#include "tag-scanner.h"
#include "tag-type.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool hadError = false;

void run(std::string source);
void runPrompt();
void runFile(std::string path);

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: ./TagScanTest [CSS FILE]" << std::endl;
        exit(1);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    return 0;
}

void runFile(std::string path) {
    std::ifstream infile(path);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    run(buffer.str());

    if (hadError) {
        exit(65);
    }
}

void runPrompt() {
    while (std::cin) {
        std::string line;
        std::cout << "> ";
        std::getline(std::cin, line);
        run(line);
        hadError = false;
    }
}

void run(std::string source) {
    TagScanner scanner(source);
    Tag tag = scanner.scanTokens();

    std::cout << "Tag: " << TagStrings[tag.type] << " | Value: " << tag.style
              << std::endl;
}
