#include "div.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Div::Div() {}

void Div::addChild(Element *element) { children.push_back(element); }

void Div::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    for (const auto &child : children) {
        child->draw(window, states);
    }
}
