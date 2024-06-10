#ifndef SFMLSURFER_DOMELEMENT_H
#define SFMLSURFER_DOMELEMENT_H

#include "composite-gui-component.h"
#include "tag-type.h"

class DomElement : public CompositeGUIComponent {
  public:
    TagType type = OTHER;
};

#endif // !SFMLSURFER_DOMELEMENT_H
