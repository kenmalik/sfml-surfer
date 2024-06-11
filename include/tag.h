#ifndef SFMLSURFER_TAG_H
#define SFMLSURFER_TAG_H

#include "tag-type.h"
#include <string>

struct Tag {
    TagType type = OTHER;
    std::string style = "";
    std::string className = "";
};

#endif // !SFMLSURFER_TAG_H
