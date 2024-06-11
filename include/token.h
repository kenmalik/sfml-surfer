#ifndef SFMLSURFER_TOKEN_H
#define SFMLSURFER_TOKEN_H

#include "token-type.h"
#include <ostream>
#include <string>

class Token {
  public:
    const TokenType type;
    const std::string lexeme;
    const std::string value;
    const int line;

    Token(TokenType type, std::string lexeme, std::string value, int line);
    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

#endif // !SFMLSURFER_TOKEN_H
