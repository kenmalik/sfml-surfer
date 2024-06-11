#include "css-property-type.h"
#include "css-scanner.h"
#include "css-token.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

bool hadError = false;

void run(std::string source);
void runPrompt();
void runFile(std::string path);

int main(int argc, char *argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: ./CssTest [CSS FILE]" << std::endl;
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
    CssScanner scanner(source);
    std::vector<Ruleset> rulesets = scanner.scanFile();

    for (const auto &ruleset : rulesets) {
        std::cout << "Ruleset " << ruleset.selector << " " << ruleset.type
                  << std::endl;
        for (const auto &value : ruleset.properties) {
            std::cout << "  " << CSS_PROPERTY_STRINGS.at(value.type)
                      << std::endl;
        }
        std::cout << std::endl;
    }
}
