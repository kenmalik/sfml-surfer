#ifndef SFMLSURFER_TOKENTYPE_H
#define SFMLSURFER_TOKENTYPE_H

enum TokenType {
    // Single-character tokens.
    DOT,
    POUND,

    // One or two character tokens.
    EQUAL,

    // Literals.
    STRING,
    TAG,
    CLOSING_TAG,
    TEXT_CONTENT,
    NUMBER,
    IDENTIFIER,

    // Keywords.
    P,
    A,
    DIV,
    H1,
    H2,
    H3,
    H4,

    END
};

static const char *EnumStrings[] = {
    "dot",          "pound",  "equal",      "string", "tag",   "closing tag",
    "text content", "number", "identifier", "p tag",  "a tag", "div tag",
    "h1 tag",       "h2 tag", "h3 tag",     "h4 tag", "end"};

#endif // !SFMLSURFER_TOKENTYPE_H
