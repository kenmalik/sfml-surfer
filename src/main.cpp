#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

constexpr float kScreenWidth = 1400;
constexpr float kScreenHeight = 1000;

int main() {
  std::cout << "Test" << std::endl;
  sf::CircleShape circle(100);

  sf::RenderWindow window(sf::VideoMode(kScreenWidth, kScreenHeight), "Window");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    window.draw(circle);

    window.display();
  }
  return 0;
}
