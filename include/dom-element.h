#ifndef SFMLSURFER_DOMELEMENT_H
#define SFMLSURFER_DOMELEMENT_H

#include "composite-gui-component.h"
#include "css-token.h"
#include "tag-type.h"

class DomElement : public CompositeGUIComponent {
  public:
    TagType type = OTHER;
    std::vector<CssProperty> css;
    std::vector<std::string> classes;
};

#endif // !SFMLSURFER_DOMELEMENT_H
