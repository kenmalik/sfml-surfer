#ifndef SFMLSURFER_DIV_H
#define SFMLSURFER_DIV_H

#include "element.h"
#include <vector>

class Div : public Element {
  public:
    Div();

    void addChild(Element *element) override;

    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override;

  private:
    std::vector<Element *> children;
};

#endif // !SFMLSURFER_DIV_H
