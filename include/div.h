#ifndef SFMLSURFER_DIV_H
#define SFMLSURFER_DIV_H

#include "composite-gui-component.h"
#include "element.h"
#include <vector>

class Div : public CompositeGUIComponent {
  public:
    Div();

    void addChild(Element *element);

    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override;

  private:
    std::vector<Element *> children;
};

#endif // !SFMLSURFER_DIV_H
