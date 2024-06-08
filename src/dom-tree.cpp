#include "dom-tree.h"
#include "composite-gui-component.h"
#include "gui-component.h"
#include "padding.h"
#include "token-type.h"
#include "word.h"

#include <SFML/Graphics/Color.hpp>
#include <iostream>

DOMTree::DOMTree(const std::vector<Token> *tokens) : tokens(tokens) {
    root = new CompositeGUIComponent();
    openTags.push({root, "div"});
}

void DOMTree::render() {
    std::cout << "\nRendering Tokens:\n" << std::endl;
    while (!isAtEnd()) {
        processToken();
    }
    std::cout << "\nApplying Styles:\n" << std::endl;
    applyStyles();
}

void DOMTree::addTag(const std::string &type) {
    if (openTags.empty()) {
        return;
    }

    auto composite =
        dynamic_cast<CompositeGUIComponent *>(openTags.top().first);
    if (!composite) {
        std::cerr << "Cannot add child to " << type << std::endl;
        exit(1);
    }

    auto child = new CompositeGUIComponent();
    composite->addChild(child);
    openTags.push({child, type});
}

void DOMTree::closeTag() { openTags.pop(); }

void DOMTree::addText(const std::string &content) {
    std::cout << "Adding text: " << content << std::endl;
    auto text = new Word();
    text->setText(content);
    auto composite =
        dynamic_cast<CompositeGUIComponent *>(openTags.top().first);
    if (!composite) {
        std::cerr << "Cannot add text" << std::endl;
        exit(1);
    }
    composite->addChild(text);
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
        addTag(token.value);
        break;
    case CLOSING_TAG:
        if (token.value == openTags.top().second) {
            std::cout << "Closed " << token.value << std::endl;
            closeTag();
        } else {
            std::cerr << "Invalid closing tag" << std::endl;
            exit(1);
        }
        break;
    case TEXT_CONTENT:
        addText(token.value);
        break;
    case END:
        return;
    default:
        std::cerr << "Unkown token" << std::endl;
        exit(1);
    }
}

const Token &DOMTree::advance() { return tokens->at(current++); }

bool DOMTree::isAtEnd() { return current >= tokens->size(); }

void DOMTree::applyStyles() {
    currentY = 0;
    postOrderTraversal(root, &DOMTree::styleComponent);
}

void DOMTree::styleComponent(GuiComponent *&component) {
    component->setPosition(component->getPosition().x, currentY);
    auto padded = new Padding(component, 20, 50, 0);
    padded->setBackgroundColor(sf::Color(200, 100, 50, 50));
    component = padded;
    currentY += component->getGlobalBounds().height;
}

void DOMTree::postOrderTraversal(GuiComponent *&node,
                                 void (DOMTree::*func)(GuiComponent *&param)) {
    auto composite = dynamic_cast<CompositeGUIComponent *>(node);
    if (!composite) {
        return;
    }

    CompositeGUIComponent::childIterator iter;
    for (iter = composite->childrenBegin(); iter != composite->childrenEnd();
         ++iter) {
        postOrderTraversal(*iter, func);
    }
    if (node != root) {
        ((*this).*func)(node);
    }
}
