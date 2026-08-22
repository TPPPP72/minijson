#pragma once

#include <Token.hpp>
#include <format>
#include <iostream>

inline const char *getTokenKindName(TokenKind kind)
{
    switch (kind)
    {
    case TokenKind::NoneKind:
        return "NoneKind";
    case TokenKind::Number:
        return "Number";
    case TokenKind::String:
        return "String";
    case TokenKind::LeftBracket:
        return "LeftBracket";
    case TokenKind::RightBracket:
        return "RightBracket";
    case TokenKind::LeftBrace:
        return "LeftBrace";
    case TokenKind::RightBrace:
        return "RightBrace";
    case TokenKind::Colon:
        return "Colon";
    case TokenKind::Comma:
        return "Comma";
    }
    std::cerr << "getTokenKindName Error\n";
    std::exit(1);
}

inline std::string formatToken(const Token *token)
{
    return std::format("loc:{} kind:{} content:\'{}\' len:{}", token->loc,
                       getTokenKindName(token->kind), token->getContent(),
                       token->len);
}
