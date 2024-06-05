#include "text-content.h"

TextContent::TextContent() : TextContent("") {}

TextContent::TextContent(const std::string &text) { setText(text); }

void TextContent::addChild(Element *element) {}

void TextContent::draw(sf::RenderTarget &window,
                       sf::RenderStates states) const {
    Word::draw(window, states);
}
