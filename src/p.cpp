#include "p.h"

PTag::PTag() {}

void PTag::addChild(Element *element) { children.push_back(element); }

void PTag::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    for (const Element *child : children) {
        child->draw(window, states);
    }
}
