#include "css-scanner.h"
#include "css-property-type.h"
#include "css-token.h"
#include "surfer.h"
#include <iostream>
#include <stdexcept>

const std::map<std::string, CssPropertyType> CssScanner::types = {
    {"color", COLOR},
    {"background-color", BACKGROUND_COLOR},
    {"margin", MARGIN},
    {"padding", PADDING},
    {"text-decoration", TEXT_DECORATION},
};

CssScanner::CssScanner(std::string source) : source(source) {}

std::vector<CssProperty> CssScanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    return tokens;
}

bool CssScanner::isAtEnd() { return current >= source.length(); }

void CssScanner::scanToken() {
    char c = advance();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        line++;
        break;
    case ':':
        pushingProperty = true;
        break;
    case ';':
        pushingProperty = false;
        break;
    default:
        if (isAlphaNumeric(c)) {
            readProperty();
        } else {
            std::string errorMsg = "Unexpected character " + std::string(1, c);
            Surfer::error(line, errorMsg);
        }
        break;
    }
}

char CssScanner::advance() { return source.at(current++); }

void CssScanner::addToken(CssPropertyType type) { addToken(type, ""); }

void CssScanner::addToken(CssPropertyType type, std::string value) {
    std::string text = source.substr(start, current - start);
    CssProperty property;
    property.type = type;
    property.values.push_back(value);
    tokens.push_back({type, {value}});
}

bool CssScanner::match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source.at(current) != expected) {
        return false;
    }
    current++;
    return true;
}

char CssScanner::peek() {
    if (isAtEnd()) {
        return '\0';
    }
    return source.at(current);
}

bool CssScanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
           c == '-' || c == '.';
}

bool CssScanner::isDigit(char c) { return c >= '0' && c <= '9'; }

bool CssScanner::isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

void CssScanner::readProperty() {
    while (isAlphaNumeric(peek()) && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
        }
        advance();
    }

    if (isAtEnd()) {
        Surfer::error(line, "Unterminated property");
        return;
    }

    std::string value = source.substr(start, current - start);

    if (!pushingProperty) {
        try {
            tokens.push_back({types.at(value), {}});
            currentPropertyList = &tokens.back().values;
        } catch (std::out_of_range e) {
            std::cerr << "Unsupported CSS property " << value << std::endl;
            exit(1);
        }
    } else {
        currentPropertyList->push_back(value);
    }
}
