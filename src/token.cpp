#include "token.h"
#include <iomanip>

Token::Token(TokenType type, std::string lexeme, std::string value, int line)
    : type(type), lexeme(lexeme), value(value), line(line) {}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << std::setw(20) << EnumStrings[token.type] << " - "
       << (token.type == TEXT_CONTENT ? token.value : token.lexeme);
    return os;
}
