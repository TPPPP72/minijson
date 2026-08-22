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
