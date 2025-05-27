#include <cxxopts.hpp>

#include <iostream>

#include "surfer.h"
#include "config.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options("SFML Surfer", "A CLI tool that renders HTML and CSS as SFML components");

    options.add_options()
        ("h,help", "Show help")
        ("v,version", "Show version")
        ("f,file", "Input HTML file", cxxopts::value<std::string>())
        ("s,style", "Input stylesheet", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    } else if (result.count("version")) {
        std::cout << "Version " << SFML_SURFER_VERSION_MAJOR << "." << SFML_SURFER_VERSION_MINOR << std::endl;
        return 0;
    }

    std::string file;
    if (result.count("file")) {
        file = result["file"].as<std::string>();
    }

    std::string style;
    if (result.count("style")) {
        style = result["style"].as<std::string>();
    }

    if (!file.empty() && !style.empty()) {
        Surfer::runFile(file, style);
    } else if (!file.empty()) {
        Surfer::runFile(file);
    } else {
        Surfer::runPrompt();
    }

    return 0;
}
