#ifndef SFMLSURFER_DOMTREE_H
#define SFMLSURFER_DOMTREE_H

#include "css-scanner.h"
#include "gui-component.h"
#include "token.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <stack>
#include <string>
#include <vector>

class DOMTree : public sf::Drawable {
  public:
    DOMTree(const std::vector<Token> *tokens);

    void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

    void addTag(const std::string &content);
    void closeTag();

    void render();
    void processToken();
    void applyStyles();
    void postOrderTraversal(GuiComponent *&node,
                            void (DOMTree::*func)(GuiComponent *&param));
    void styleComponent(GuiComponent *&component);

    const Token &advance();

    bool isAtEnd();

    void addText(const std::string &content);

    void setWidth(float width);
    void setStretch(bool on);

    void clear();
    void deleteNode(GuiComponent *&node);

    void addRuleset(const std::vector<Ruleset> &ruleset);

  private:
    bool stretch = false;
    float width = 0;

    const std::vector<Token> *tokens;
    std::vector<Ruleset> cssRules;
    std::stack<std::pair<GuiComponent *, std::string>> openTags;
    GuiComponent *root = nullptr;

    int currentToken = 0;

    float currentY = 0;
};

#endif // !SFMLSURFER_DOMTREE_H
