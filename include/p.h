#ifndef SFMLSURFER_P_H
#define SFMLSURFER_P_H

#include "element.h"
#include <vector>

class PTag : public Element {
  public:
    PTag();

    void addChild(Element *element) override;

    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override;

  private:
    std::vector<Element *> children;
};

#endif // !SFMLSURFER_P_H
