#ifndef SFMLSURFER_DOMTREE_H
#define SFMLSURFER_DOMTREE_H

#include "element.h"
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

    void addTag(const std::string &type);

    void render();
    void processToken();

    const Token &advance();

    bool isAtEnd();

    void addText(const std::string &content);

  private:
    const std::vector<Token> *tokens;
    std::stack<std::pair<Element *, std::string>> openTags;
    std::string prevText;
    Element *root = nullptr;

    int current = 0;

    float currentY = 0;
};

#endif // !SFMLSURFER_DOMTREE_H
