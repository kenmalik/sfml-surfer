#ifndef SFMLSURFER_DOMTREE_H
#define SFMLSURFER_DOMTREE_H

#include "composite-gui-component.h"
#include "element.h"
#include "gui-component.h"
#include "p.h"
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
    static constexpr unsigned int defaultCharacterSize = 18;
    static const std::map<std::string, TagType> tagTypeMap;
    const std::vector<Token> *tokens;
    std::stack<std::pair<GuiComponent *, std::string>> openTags;
    std::string prevText;
    GuiComponent *root = nullptr;

    int current = 0;

    float currentY = 0;
};

#endif // !SFMLSURFER_DOMTREE_H
