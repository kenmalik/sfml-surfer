#include "dom-tree.h"
#include "color-manager.h"
#include "composite-gui-component.h"
#include "css-property-type.h"
#include "css-scanner.h"
#include "dom-element.h"
#include "font-enum.h"
#include "gui-component.h"
#include "padding.h"
#include "styler.h"
#include "tag-scanner.h"
#include "tag-type.h"
#include "token-type.h"
#include "word.h"

#include <SFML/Graphics/Color.hpp>
#include <iostream>

DOMTree::DOMTree(const std::vector<Token> *tokens) : tokens(tokens) {
    root = new DomElement();
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

void DOMTree::addTag(const std::string &tagContent) {
    TagScanner scanner(tagContent);
    Tag tag = scanner.scanTokens();

    if (openTags.empty()) {
        return;
    }

    auto composite =
        dynamic_cast<CompositeGUIComponent *>(openTags.top().first);
    if (!composite) {
        std::cerr << "Cannot add child to " << tagContent << std::endl;
        exit(1);
    }

    auto child = new DomElement();
    composite->addChild(child);
    child->type = tag.type;
    if (tag.style != "") {
        std::cout << "Styled " << scanner.tagString << std::endl;
        CssScanner cssScanner(tag.style);
        child->css = cssScanner.scanTokens();
    }

    openTags.push({child, scanner.tagString});
}

void DOMTree::closeTag() { openTags.pop(); }

void DOMTree::addText(const std::string &content) {
    auto text = new Word();
    text->setText(content);
    text->setCharacterSize(defaultCharacterSize);
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
    auto composite = dynamic_cast<DomElement *>(component);
    // Don't know why this works at positioning items but it does
    if (composite && composite->getChildCount() <= 1) {
        component->setPosition(component->getPosition().x, currentY);
    }

    auto styler = Styler(composite->type);
    styler.style(component);
    currentY =
        component->getGlobalBounds().top + component->getGlobalBounds().height;
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
