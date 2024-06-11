#ifndef SFMLSURFER_CSSPROPERTY_H
#define SFMLSURFER_CSSPROPERTY_H

#include "css-property-type.h"
#include <string>
#include <vector>

struct CssProperty {
    CssPropertyType type;
    std::vector<std::string> values;
};

#endif // !SFMLSURFER_CSSPROPERTY_H
