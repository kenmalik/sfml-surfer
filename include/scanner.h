#ifndef SFMLSURFER_SCANNER_H
#define SFMLSURFER_SCANNER_H

#include "token-type.h"
#include "token.h"
#include <stack>
#include <vector>

class Scanner {
  public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();

  private:
    int start = 0;
    int current = 0;
    int line = 1;

    const std::string source;
    std::vector<Token> tokens;

    bool isAtEnd();

    void scanToken();
    char advance();

    void addToken(TokenType type);
    void addToken(TokenType type, std::string value);

    bool match(char expected);
    char peek();

    void tag();
    void textContent();

    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);

    void openTag(std::string tagName);
    void closeTag(std::string tagName);

    std::stack<std::string> openTags;
};

#endif // !SFMLSURFER_SCANNER_H
