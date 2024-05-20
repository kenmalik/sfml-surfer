#include "scanner.h"
#include "surfer.h"
#include "token-type.h"
#include <iostream>

const std::map<std::string, TokenType> Scanner::keywords = {
    {"p", P},   {"a", A},   {"div", DIV}, {"h1", H1},
    {"h2", H2}, {"h3", H3}, {"h4", H4}};

Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back({END, "", "", 0});
    return tokens;
}

bool Scanner::isAtEnd() { return current >= source.length(); }

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case '=':
        addToken(EQUAL);
        break;
    case '>':
        addToken(GREATER);
        break;
    case '<':
        addToken(match('/') ? LESS_SLASH : LESS);
        break;
    case '"':
        string();
        break;
    default:
        if (isAlpha(c)) {
            identifier();
        } else {
            Surfer::error(line, "Unexpected character");
        }
        break;
    }
}

char Scanner::advance() { return source.at(current++); }

void Scanner::addToken(TokenType type) { addToken(type, ""); }

void Scanner::addToken(TokenType type, std::string value) {
    std::string text = source.substr(start, current - start);
    tokens.push_back({type, text, value, line});
}

bool Scanner::match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source.at(current) != expected) {
        return false;
    }
    current++;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) {
        return '\0';
    }
    return source.at(current);
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (isAtEnd()) {
        Surfer::error(line, "Unterminated string");
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - start - 2);
    addToken(STRING, value);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

void Scanner::identifier() {
    while (isAlphaNumeric(peek())) {
        advance();
    }

    TokenType type;
    std::string text = source.substr(start, current - start);
    auto iter = keywords.find(text);
    if (iter == keywords.end()) {
        type = IDENTIFIER;
    } else {
        type = iter->second;
    }
    addToken(type);
}
