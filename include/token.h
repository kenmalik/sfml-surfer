#ifndef SFMLSURFER_TOKEN_H
#define SFMLSURFER_TOKEN_H

#include "token-type.h"
#include <string>

struct Token {
    const TokenType type;
    const std::string lexeme;
    const std::string value;
    const int line;
};

#endif // !SFMLSURFER_TOKEN_H
