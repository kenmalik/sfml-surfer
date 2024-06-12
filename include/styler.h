#ifndef SFMLSURFER_STYLER_H
#define SFMLSURFER_STYLER_H

#include "css-scanner.h"
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

    void setWidth(float width);
    void setStretch(bool on);

    void addRuleset(const std::vector<Ruleset> &ruleset);

  private:
    static constexpr float DEFAULT_SIZE = 18;

    std::vector<Ruleset> cssRules;

    float width = 0;
    bool stretch = false;

    FontEnum font = UBUNTU_R;
    float sizeRatio = 1;

    std::string textStyle = "none";
    sf::Color textColor = sf::Color::Black;
    sf::Color paddingColor = sf::Color::Transparent;

    Spacing padding = {0, 0, 0, 0};
    Spacing margin = {0, 0, 0, 0};
};

#endif // !SFMLSURFER_STYLER_H
