#ifndef SFMLSURFER_TEXTCONTENT_H
#define SFMLSURFER_TEXTCONTENT_H

#include "element.h"
#include "word.h"

class TextContent : public Element, public Word {
  public:
    TextContent();
    TextContent(const std::string &text);

    void addChild(Element *element) override;

    virtual void draw(sf::RenderTarget &window,
                      sf::RenderStates states) const override;
};

#endif // !SFMLSURFER_TEXTCONTENT_H
