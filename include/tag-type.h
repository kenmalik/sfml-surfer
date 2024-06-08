#ifndef SFMLSURFER_TAGTYPE_H
#define SFMLSURFER_TAGTYPE_H

enum TagType { P, DIV, H1, H2, H3, H4, H5, H6, INPUT, LABEL, OTHER };

static const char *TagStrings[] = {
    "P tag",  "DIV tag", "H1 tag",    "H2 tag",    "H3 tag",    "H4 tag",
    "H5 tag", "H6 tag",  "INPUT tag", "LABEL tag", "OTHER  tag"};

#endif // !SFMLSURFER_TAGTYPE_H
