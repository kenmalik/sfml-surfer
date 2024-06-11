#ifndef SFMLSURFER_DOMTREE_H
#define SFMLSURFER_DOMTREE_H

#include "gui-component.h"
#include "tag-type.h"
#include "token.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <map>
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

  private:
    const std::vector<Token> *tokens;
    std::stack<std::pair<GuiComponent *, std::string>> openTags;
    GuiComponent *root = nullptr;

    int currentToken = 0;

    float currentY = 0;
};

#endif // !SFMLSURFER_DOMTREE_H
