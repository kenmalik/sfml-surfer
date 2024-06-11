#ifndef SFMLSURFER_CSSSCANNER_H
#define SFMLSURFER_CSSSCANNER_H

#include "css-property-type.h"
#include "css-token.h"
#include <vector>

class CssScanner {
  public:
    CssScanner(std::string source);
    std::vector<CssProperty> scanTokens();

  private:
    int start = 0;
    int current = 0;
    int line = 1;

    const std::string source;
    std::vector<CssProperty> tokens;

    bool isAtEnd();

    void scanToken();
    char advance();

    void addToken(CssPropertyType type);
    void addToken(CssPropertyType type, std::string value);

    bool match(char expected);
    char peek();

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);

    void readProperty();

    std::vector<std::string> *currentPropertyList;
    bool pushingProperty = false;

    static const std::map<std::string, CssPropertyType> types;
};

#endif // !SFMLSURFER_CSSSCANNER_H
