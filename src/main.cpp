#include "font-enum.h"
#include "font-manager.h"
#include "surfer.h"
#include "word.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

constexpr float kScreenWidth = 1400;
constexpr float kScreenHeight = 1000;

int main(int argc, char *argv[]) {
    sf::CircleShape circle(100);
    sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight),
                            "Window");

    Word word;
    word.setString("Hello");
    word.setFont(FontManager::getFont(UBUNTU_B));
    word.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(word);
        window.display();
    }

    // if (argc > 2) {
    //     std::cerr << "Usage: sfml-surfer [html file]" << std::endl;
    // } else if (argc == 2) {
    //     Surfer::runFile(argv[1]);
    // } else {
    //     Surfer::runPrompt();
    // }

    return 0;
}
