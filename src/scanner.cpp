#include "scanner.h"
#include "surfer.h"
#include "token-type.h"
#include <algorithm>

Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    if (!openTags.empty()) {
        Surfer::error(line, "Unclosed tags");
    }

    tokens.push_back({END, "EOF", "", 0});
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
    case '<':
        tag();
        break;
    case '"':
        string();
        break;
    default:
        if (isAlpha(c)) {
            textContent();
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

void Scanner::tag() {
    bool closing = match('/') ? true : false;
    while (peek() != '>' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (isAtEnd()) {
        Surfer::error(line, "Unterminated tag");
        return;
    }

    advance();

    std::string value = source.substr(start + (closing ? 2 : 1),
                                      current - start - (closing ? 3 : 2));
    addToken(closing ? CLOSING_TAG : TAG, value);
    if (closing) {
        closeTag(value);
    } else {
        openTag(value);
    }
}

void Scanner::textContent() {
    while (peek() != '<' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (isAtEnd()) {
        Surfer::error(line, "Unclosed tag");
        return;
    }

    std::string content = source.substr(start, current - start);
    std::replace(content.begin(), content.end(), '\n', ' ');
    addToken(TEXT_CONTENT, content);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool Scanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

void Scanner::openTag(std::string tagName) { openTags.push(tagName); }

void Scanner::closeTag(std::string tagName) {
    if (!openTags.empty() && openTags.top() == tagName) {
        openTags.pop();
    } else {
        Surfer::error(line, "Unexpected closing of tag " + tagName);
    }
}
