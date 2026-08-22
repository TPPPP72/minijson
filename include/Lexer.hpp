#pragma once

#include <Token.hpp>
#include <iostream>
#include <vector>

class TokenViewer
{
public:
    TokenViewer() = default;
    TokenViewer(const std::vector<Token> &tokens) : m_tokens(&tokens) {}

    const Token *getToken() const noexcept { return &(*m_tokens)[m_index]; }

    void skipToken() noexcept { ++m_index; }

    bool atEnd() const noexcept { return m_index == m_tokens->size(); }

private:
    const std::vector<Token> *m_tokens;
    std::uint64_t m_index{0};
};

class Lexer
{
public:
    Lexer() { tokens.reserve(4096); }

    TokenViewer tokenize(std::string_view source)
    {
        std::uint64_t offset{};
        std::uint64_t maxlen = source.length();

        while (offset < maxlen)
        {
            // Skip blank
            if (source[offset] == ' ' || source[offset] == '\t' ||
                source[offset] == '\n')
            {
                ++offset;
                continue;
            }

            // Number
            if (std::isdigit(source[offset]))
            {
                std::uint64_t len{1};

                while (offset + len < maxlen &&
                       (std::isdigit(source[offset + len]) ||
                        source[offset + len] == '.'))
                    ++len;

                tokens.emplace_back(source, TokenKind::Number, offset, len);
                offset += len;
                continue;
            }

            // Punctuator
            TokenKind kind = TokenKind::NoneKind;
            switch (source[offset])
            {
            case '[':
                kind = TokenKind::LeftBracket;
                break;
            case ']':
                kind = TokenKind::RightBracket;
                break;
            case '{':
                kind = TokenKind::LeftBrace;
                break;
            case '}':
                kind = TokenKind::RightBrace;
                break;
            }
            if (kind != TokenKind::NoneKind)
            {
                tokens.emplace_back(source, kind, offset, 1);
                offset += 1;
                continue;
            }

            std::cerr << "Tokenize Error at offset " << offset << " \'"
                      << source[offset] << "\'\n";
            std::exit(1);
        }

        return TokenViewer(tokens);
    }

private:
    std::string m_source;
    std::vector<Token> tokens;
};
