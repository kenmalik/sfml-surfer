#include "styler.h"
#include "color-manager.h"
#include "dom-element.h"
#include "margin.h"
#include "padding.h"
#include "word.h"

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

    auto padded = new Padding(
        component, DEFAULT_SIZE * padding.top, DEFAULT_SIZE * padding.right,
        DEFAULT_SIZE * padding.bottom, DEFAULT_SIZE * padding.left);
    auto margined = new Margin(
        padded, DEFAULT_SIZE * margin.top, DEFAULT_SIZE * margin.right,
        DEFAULT_SIZE * margin.bottom, DEFAULT_SIZE * margin.left);

    if (!composite->css.empty()) {
        for (auto &style : composite->css) {
            if (style.type == BACKGROUND_COLOR) {
                padded->setBackgroundColor(
                    ColorManager::getColor(style.values.at(0)));
            }
        }
    }
    component = margined;
}
