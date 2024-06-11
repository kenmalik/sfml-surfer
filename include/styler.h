#ifndef SFMLSURFER_STYLER_H
#define SFMLSURFER_STYLER_H

#include "css-token.h"
#include "font-enum.h"
#include "gui-component.h"
#include "tag-type.h"
#include <SFML/Graphics/Color.hpp>

struct Spacing {
    float top;
    float right;
    float bottom;
    float left;
};

class Styler {
  public:
    Styler(TagType type);
    void style(GuiComponent *&component);
    void overwriteStyles(const CssProperty &style);

  private:
    static constexpr float DEFAULT_SIZE = 18;

    FontEnum font = UBUNTU_R;
    float sizeRatio = 1;

    std::string textStyle = "none";
    sf::Color textColor = sf::Color::Black;
    sf::Color paddingColor = sf::Color::Transparent;

    Spacing padding = {0, 0, 0, 0};
    Spacing margin = {0, 0, 0, 0};
};

#endif // !SFMLSURFER_STYLER_H