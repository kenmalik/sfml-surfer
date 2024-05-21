#ifndef SFMLSURFER_TAGTYPE_H
#define SFMLSURFER_TAGTYPE_H

enum TagType {
    P,
    A,
    DIV,
    H1,
    H2,
    H3,
    H4,
};

static const char *TagStrings[] = {"p tag",  "a tag",  "div tag", "h1 tag",
                                   "h2 tag", "h3 tag", "h4 tag",  "end"};

#endif // !SFMLSURFER_TAGTYPE_H
