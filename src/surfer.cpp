#include "surfer.h"
#include "scanner.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool Surfer::hadError = false;

void Surfer::runFile(std::string path) {
    std::ifstream infile(path);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    run(buffer.str());

    if (hadError) {
        exit(65);
    }
}

void Surfer::runPrompt() {
    while (std::cin) {
        std::string line;
        std::cout << "> ";
        std::getline(std::cin, line);
        run(line);
        hadError = false;
    }
}

void Surfer::run(std::string source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    for (auto &token : tokens) {
        std::cout << token << std::endl;
    }
}

void Surfer::error(int line, std::string message) { report(line, "", message); }

void Surfer::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " + message
              << std::endl;
    hadError = true;
}
