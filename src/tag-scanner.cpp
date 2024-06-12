#include "tag-scanner.h"
#include "surfer.h"

TagScanner::TagScanner(std::string source) : source(source) {}

Tag TagScanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    return tag;
}

bool TagScanner::isAtEnd() { return current >= source.length(); }

void TagScanner::scanToken() {
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

char TagScanner::advance() { return source.at(current++); }

bool TagScanner::match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source.at(current) != expected) {
        return false;
    }
    current++;
    return true;
}

char TagScanner::peek() {
    if (isAtEnd()) {
        return '\0';
    }
    return source.at(current);
}

void TagScanner::string() {
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
    if (currentProperty != "") {
        if (currentProperty == "style") {
            tag.style = value;
        } else if (currentProperty == "class") {
            tag.className = value;
        }
    }
}

void TagScanner::textContent() {
    while (isAlphaNumeric(peek())) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    std::string content = source.substr(start, current - start);
    if (peek() == '=') {
        currentProperty = content;
    } else {
        tag.type = tagTypeMap.at(content);
        tagString = content;
    }
}

bool TagScanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
           c == '-';
}

bool TagScanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool TagScanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }
