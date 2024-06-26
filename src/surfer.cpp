#include "surfer.h"
#include "css-scanner.h"
#include "dom-tree.h"
#include "scanner.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::string Surfer::cssPath;
bool Surfer::hadError = false;

void Surfer::runFile(std::string htmlPath, std::string cssPath) {
    Surfer::cssPath = cssPath;
    runFile(htmlPath);
}

void Surfer::runFile(std::string path) {
    std::ifstream infile(path);
    if (infile.fail()) {
        std::cerr << "Error opening html file " << path << std::endl;
        exit(1);
    }
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

    Surfer::display(&tokens);
}

void Surfer::error(int line, std::string message) { report(line, "", message); }

void Surfer::report(int line, std::string where, std::string message) {
    std::cerr << "[line " << line << "] Error " << where << ": " + message
              << std::endl;
    hadError = true;
}

void Surfer::display(const std::vector<Token> *tokens) {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "SFML Surfer");
    DOMTree dom(tokens);
    dom.setWidth(window.getSize().x);
    dom.setStretch(true);
    if (!cssPath.empty()) {
        dom.addRuleset(readCssFile());
    }
    dom.render();

    sf::View view = window.getView();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                view.setSize(window.getSize().x, window.getSize().y);
                view.setCenter(
                    window.getSize().x / 2.f,
                    std::max(view.getCenter().y, window.getSize().y / 2.f));
                window.setView(view);
                dom.setWidth(window.getSize().x);
                dom.render();
            } else if (event.type == sf::Event::MouseWheelMoved) {
                float offsetY = -event.mouseWheel.delta * 50;
                if (view.getCenter().y + offsetY >= window.getSize().y / 2.f) {
                    view.move(0, offsetY);
                } else {
                    view.setCenter(window.getSize().x / 2.f,
                                   window.getSize().y / 2.f);
                }
                window.setView(view);
            }
        }
        window.clear(sf::Color::White);
        window.draw(dom);
        window.display();
    }
}

std::vector<Ruleset> Surfer::readCssFile() {
    std::ifstream infile(cssPath);
    if (infile.fail()) {
        std::cerr << "Error opening css file " << cssPath << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << infile.rdbuf();
    return CssScanner(buffer.str()).scanFile();
}
