#ifndef SFMLSURFER_ELEMENT_H
#define SFMLSURFER_ELEMENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

class Element : sf::Drawable {
  public:
    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override = 0;
    virtual void addChild(Element *element) = 0;
    // void removeChild(Element element);

  private:
};

#endif // !SFMLSURFER_ELEMENT_H
