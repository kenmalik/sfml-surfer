#include "surfer.h"
#include "dom-tree.h"
#include "scanner.h"
#include "word.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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

    // for (auto &token : tokens) {
    //     std::cout << token << std::endl;
    //     std::cout << " -" << token.type << std::endl;
    // }

    Surfer::display(&tokens);
}

void Surfer::error(int line, std::string message) { report(line, "", message); }

void Surfer::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " + message
              << std::endl;
    hadError = true;
}

void Surfer::display(const std::vector<Token> *tokens) {
    DOMTree dom(tokens);
    dom.render();

    sf::CircleShape circle(100);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "SFML Surfer");

    // Word word;
    // word.setText("SFML Surfer");
    // word.setFont(UBUNTU_R);
    // word.setTextColor(sf::Color::White);
    // word.setPadding(20, 80);
    // word.setBackgroundColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        // window.draw(word);
        window.draw(dom);
        window.display();
    }
}
