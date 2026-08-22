#pragma once

#include <cstdint>
#include <string_view>

enum class TokenKind
{
    NoneKind,
    Number,
    LeftBracket,  // '['
    RightBracket, // ']'
    LeftBrace,    // '{'
    RightBrace,   // '}'
    Colon,        // ':'
    Comma,        // ','
};

struct Token
{
    std::string_view source;
    TokenKind kind;
    std::uint64_t loc;
    std::uint64_t len;

    Token() = default;
    Token(std::string_view s, TokenKind k, std::uint64_t loc, std::uint64_t len)
        : source(s), kind(k), loc(loc), len(len)
    {
    }
    std::string_view getContent() const { return source.substr(loc, len); }
};
