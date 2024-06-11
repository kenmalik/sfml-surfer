#include "styler.h"
#include "color-manager.h"
#include "css-token.h"
#include "dom-element.h"
#include "margin.h"
#include "padding.h"
#include "word.h"
#include <iostream>

Styler::Styler(TagType type) {
    switch (type) {
    case P:
        margin = {1, 0, 1, 0};
        break;
    case DIV:
        break;
    case H1:
        sizeRatio = 2;
        margin = {.67, 0, .67, 0};
        font = UBUNTU_B;
        break;
    case H2:
        sizeRatio = 1.5;
        margin = {.83, 0, .83, 0};
        font = UBUNTU_B;
        break;
    case H3:
        sizeRatio = 1.17;
        margin = {1, 0, 1, 0};
        font = UBUNTU_B;
        break;
    case H4:
        margin = {1.33, 0, 1.33, 0};
        font = UBUNTU_B;
        break;
    case H5:
        sizeRatio = .83;
        margin = {1.67, 0, 1.67, 0};
        font = UBUNTU_B;
        break;
    case H6:
        sizeRatio = .67;
        margin = {2.33, 0, 2.33, 0};
        font = UBUNTU_B;
        break;
    case INPUT:
        break;
    case LABEL:
        break;
    case OTHER:
        break;
    }
}

void Styler::style(GuiComponent *&component) {
    auto composite = dynamic_cast<DomElement *>(component);
    for (auto iter = composite->childrenBegin();
         iter != composite->childrenEnd(); ++iter) {
        auto word = dynamic_cast<Word *>(*iter);
        if (word) {
            word->setFont(font);
            word->setCharacterSize(DEFAULT_SIZE * sizeRatio);
            for (auto &style : composite->css) {
                if (style.type == COLOR) {
                    word->setTextColor(
                        ColorManager::getColor(style.values.at(0)));
                } else if (style.type == TEXT_DECORATION &&
                           style.values.at(0) == "underline") {
                    word->setIsUnderlined(true);
                }
            }
        }
    }

    // Inline overwrite defaults
    for (auto &style : composite->css) {
        overwriteStyles(style);
    }

    auto padded = new Padding(
        component, DEFAULT_SIZE * padding.top, DEFAULT_SIZE * padding.right,
        DEFAULT_SIZE * padding.bottom, DEFAULT_SIZE * padding.left);
    auto margined = new Margin(
        padded, DEFAULT_SIZE * margin.top, DEFAULT_SIZE * margin.right,
        DEFAULT_SIZE * margin.bottom, DEFAULT_SIZE * margin.left);

    padded->setBackgroundColor(paddingColor);

    component = margined;
}

void Styler::overwriteStyles(const CssProperty &style) {
    if (style.type == BACKGROUND_COLOR) {
        paddingColor = ColorManager::getColor(style.values.at(0));
    } else if (style.type == PADDING) {
        switch (style.values.size()) {
        case 1: {
            float pad = stod(style.values.at(0));
            padding.top = pad;
            padding.right = pad;
            padding.bottom = pad;
            padding.left = pad;
        } break;
        case 2: {
            float padTopBottom = stod(style.values.at(0));
            float padLeftRight = stod(style.values.at(1));
            padding.top = padTopBottom;
            padding.right = padLeftRight;
            padding.bottom = padTopBottom;
            padding.left = padLeftRight;
        } break;
        case 3: {
            float padTop = stod(style.values.at(0));
            float padLeftRight = stod(style.values.at(1));
            float padBottom = stod(style.values.at(2));
            padding.top = padTop;
            padding.right = padLeftRight;
            padding.bottom = padBottom;
            padding.left = padLeftRight;
        } break;
        case 4: {
            float padTop = stod(style.values.at(0));
            float padRight = stod(style.values.at(1));
            float padBottom = stod(style.values.at(2));
            float padLeft = stod(style.values.at(3));
            padding.top = padTop;
            padding.right = padRight;
            padding.bottom = padBottom;
            padding.left = padLeft;
        } break;
        default:
            break;
        }
    } else if (style.type == MARGIN) {
        switch (style.values.size()) {
        case 1: {
            float marg = stod(style.values.at(0));
            margin.top = marg;
            margin.right = marg;
            margin.bottom = marg;
            margin.left = marg;
        } break;
        case 2: {
            float marginTopBottom = stod(style.values.at(0));
            float marginLeftRight = stod(style.values.at(1));
            margin.top = marginTopBottom;
            margin.right = marginLeftRight;
            margin.bottom = marginTopBottom;
            margin.left = marginLeftRight;
        } break;
        case 3: {
            float marginTop = stod(style.values.at(0));
            float marginLeftRight = stod(style.values.at(1));
            float marginBottom = stod(style.values.at(2));
            margin.top = marginTop;
            margin.right = marginLeftRight;
            margin.bottom = marginBottom;
            margin.left = marginLeftRight;
        } break;
        case 4: {
            float marginTop = stod(style.values.at(0));
            float marginRight = stod(style.values.at(1));
            float marginBottom = stod(style.values.at(2));
            float marginLeft = stod(style.values.at(3));
            margin.top = marginTop;
            margin.right = marginRight;
            margin.bottom = marginBottom;
            margin.left = marginLeft;
        } break;
        default:
            break;
        }
    }
}
