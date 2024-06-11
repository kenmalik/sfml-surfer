#ifndef SFMLSURFER_CSSPROPERTYTYPE_H
#define SFMLSURFER_CSSPROPERTYTYPE_H

#include <map>
#include <string>

enum CssPropertyType {
    COLOR,
    BACKGROUND_COLOR,
    PADDING,
    MARGIN,
    TEXT_DECORATION
};

const static std::map<CssPropertyType, std::string> CSS_PROPERTY_STRINGS = {
    {COLOR, "color"},
    {BACKGROUND_COLOR, "background-color"},
    {PADDING, "padding"},
    {MARGIN, "margin"},
    {TEXT_DECORATION, "text-decoration"}};

#endif // !SFMLSURFER_CSSPROPERTYTYPE_H
