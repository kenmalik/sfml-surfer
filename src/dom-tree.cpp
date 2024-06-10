#include "dom-tree.h"
#include "composite-gui-component.h"
#include "dom-element.h"
#include "font-enum.h"
#include "gui-component.h"
#include "padding.h"
#include "tag-type.h"
#include "token-type.h"
#include "word.h"

#include <SFML/Graphics/Color.hpp>
#include <iostream>
const std::map<std::string, TagType> DOMTree::tagTypeMap = {
    {"div", DIV}, {"p", P},   {"h1", H1}, {"h2", H2},       {"h3", H3},
    {"h4", H4},   {"h5", H5}, {"h6", H6}, {"input", INPUT}, {"label", LABEL}};

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

    auto child = new DomElement();
    composite->addChild(child);
    if (tagTypeMap.count(type)) {
        child->type = tagTypeMap.at(type);
    }
    openTags.push({child, type});
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
    auto composite = dynamic_cast<DomElement *>(component);
    // Don't know why this works at positioning items but it does
    if (composite && composite->getChildCount() <= 1) {
        component->setPosition(component->getPosition().x, currentY);
    }
    switch (composite->type) {
    case H1: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
                word->setCharacterSize(defaultCharacterSize * 2);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize * .67f, 0);
        component = padded;
    } break;
    case H2: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
                word->setCharacterSize(defaultCharacterSize * 1.5);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize * .83f, 0);
        component = padded;
    } break;
    case H3: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
                word->setCharacterSize(defaultCharacterSize * 1.17);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize, 0);
        component = padded;
    } break;
    case H4: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize * 1.33f, 0);
        component = padded;
    } break;
    case H5: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
                word->setCharacterSize(defaultCharacterSize * .83f);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize * 1.67f, 0);
        component = padded;
    } break;
    case H6: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_B);
                word->setCharacterSize(defaultCharacterSize * .67f);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize * 2.33f, 0);
        component = padded;
    } break;
    case DIV: {
        std::cout << "[TODO] Div styles" << std::endl;
    } break;
    case LABEL: {
        auto padded = new Padding(component, 0);
        component = padded;
    } break;
    case P: {
        for (auto iter = composite->childrenBegin();
             iter != composite->childrenEnd(); ++iter) {
            auto word = dynamic_cast<Word *>(*iter);
            if (word) {
                word->setFont(UBUNTU_R);
            }
        }
        auto padded = new Padding(component, defaultCharacterSize, 0);
        component = padded;
    } break;
    default:
        std::cerr << "Unsupported tag " << composite->type << std::endl;
    }
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
