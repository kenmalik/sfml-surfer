#include "token.h"

Token::Token(TokenType type, std::string lexeme, std::string value, int line)
    : type(type), lexeme(lexeme), value(value), line(line) {}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << EnumStrings[token.type] << " - " << token.lexeme << " - "
       << token.value;
    return os;
}
