#ifndef SFMLSURFER_TAGTYPE_H
#define SFMLSURFER_TAGTYPE_H

#include <map>
#include <string>

enum TagType { P, DIV, H1, H2, H3, H4, H5, H6, INPUT, LABEL, OTHER };

static const char *TagStrings[] = {"P",  "DIV", "H1",    "H2",    "H3",    "H4",
                                   "H5", "H6",  "INPUT", "LABEL", "OTHER "};

static const std::map<std::string, TagType> tagTypeMap = {
    {"div", DIV}, {"p", P},   {"h1", H1}, {"h2", H2},       {"h3", H3},
    {"h4", H4},   {"h5", H5}, {"h6", H6}, {"input", INPUT}, {"label", LABEL}};

#endif // !SFMLSURFER_TAGTYPE_H
