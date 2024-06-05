#include "dom-tree.h"
#include "div.h"
#include "p.h"
#include "text-content.h"
#include "token-type.h"
#include <iostream>

DOMTree::DOMTree(const std::vector<Token> *tokens) : tokens(tokens) {
    root = new Div();
    openTags.push({root, "div"});
}

void DOMTree::render() {
    while (!isAtEnd()) {
        processToken();
    }
}

void DOMTree::addTag(const std::string &type) {
    Div *child = new Div();
    openTags.top().first->addChild(child);
    openTags.push({child, type});
    // if (type == "div") {
    //     Div *child = new Div();
    //     openTags.top().first->addChild(child);
    //     openTags.push({child, type});
    // } else if (type == "p") {
    //     auto child = new PTag();
    //     openTags.top().first->addChild(child);
    //     openTags.push({child, type});
    // }
    // std::cout << "Added " << type << std::endl;
}

void DOMTree::addText(const std::string &content) {
    auto text = new TextContent(content);
    text->setPosition(0, currentY);
    currentY += text->getGlobalBounds().height;
    openTags.top().first->addChild(text);
}

void DOMTree::draw(sf::RenderTarget &window, sf::RenderStates states) const {
    if (root) {
        root->draw(window, states);
    }
}

void DOMTree::processToken() {
    const Token &token = advance();

    switch (token.type) {
    case TAG:
        std::cout << "Tag" << std::endl;
        addTag(token.value);
        break;
    case CLOSING_TAG:
        std::cout << "Closing tag" << std::endl;
        if (token.value == openTags.top().second) {
            std::cout << "Closed " << token.value << std::endl;
            openTags.pop();
        } else {
            std::cerr << "Invalid closing tag" << std::endl;
            exit(1);
        }
        break;
    case TEXT_CONTENT:
        std::cout << "Text content" << std::endl;
        addText(token.value);
        break;
    case END:
        std::cout << "Done" << std::endl;
        return;
    default:
        std::cerr << "Unkown token" << std::endl;
        exit(1);
    }
}

const Token &DOMTree::advance() { return tokens->at(current++); }

bool DOMTree::isAtEnd() { return current >= tokens->size(); }
