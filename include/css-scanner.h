#ifndef SFMLSURFER_CSSSCANNER_H
#define SFMLSURFER_CSSSCANNER_H

#include "css-property-type.h"
#include "css-token.h"
#include <vector>

enum SelectorType { TAG_NAME, ID_NAME, CLASS_NAME };

struct Ruleset {
    SelectorType type;
    std::string selector;
    std::vector<CssProperty> properties;
};

class CssScanner {
  public:
    CssScanner(std::string source);
    std::vector<CssProperty> scanInline();
    std::vector<Ruleset> scanFile();

  private:
    int start = 0;
    int current = 0;
    int line = 1;

    const std::string source;
    std::vector<CssProperty> properties;
    std::vector<Ruleset> rulesets;

    bool isAtEnd();

    void scanInlineToken();
    void scanFileToken();
    char advance();

    void addToken(CssPropertyType type);
    void addToken(CssPropertyType type, std::string value);

    bool match(char expected);
    char peek();

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);

    void readProperty();
    void className();

    std::vector<std::string> *currentPropertyList;
    bool pushingProperty = false;
    bool pushingRuleset = false;

    static const std::map<std::string, CssPropertyType> types;
};

#endif // !SFMLSURFER_CSSSCANNER_H
