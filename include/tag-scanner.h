#ifndef SFMLSURFER_TAGSCANNER_H
#define SFMLSURFER_TAGSCANNER_H

#include "tag-type.h"
#include "tag.h"
#include <map>

class TagScanner {
  public:
    TagScanner(std::string source);
    Tag scanTokens();
    std::string tagString = "";

  private:
    Tag tag = {OTHER, ""};

    int start = 0;
    int current = 0;
    int line = 1;

    static const std::map<std::string, TagType> tagTypeMap;
    const std::string source;

    bool isAtEnd();

    void scanToken();
    char advance();

    bool match(char expected);
    char peek();

    void string();
    void textContent();

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);

    void openTag(std::string tagName);
    void closeTag(std::string tagName);

    std::string currentProperty = "";
};

#endif // !SFMLSURFER_TAGSCANNER_H
