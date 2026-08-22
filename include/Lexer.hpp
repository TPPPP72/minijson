#pragma once

#include <Format.hpp>
#include <Token.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class TokenViewer
{
public:
    TokenViewer() = default;
    TokenViewer(const std::vector<Token> &tokens) : m_tokens(&tokens) {}

    const Token *getToken() const noexcept { return &(*m_tokens)[m_index]; }

    const Token *lookAhead(unsigned n) const noexcept
    {
        if (m_index + n > m_tokens->size() - 1)
            return nullptr;
        return &(*m_tokens)[m_index + n];
    }

    void consumeToken(TokenKind kind) noexcept
    {
        if (is(kind))
        {
            ++m_index;
            return;
        }

        std::cerr << "consumeToken Error: No matched token \'"
                  << getTokenKindName(kind) << "\'\n";
        std::exit(1);
    }

    void skipToken() noexcept { ++m_index; }

    bool is(TokenKind kind) const noexcept
    {
        return is(&(*m_tokens)[m_index], kind);
    }

    bool is(const Token *token, TokenKind kind) const noexcept
    {
        if (token)
            return kind == token->kind;

        return false;
    }

    bool atEnd() const noexcept { return m_index == m_tokens->size(); }

private:
    const std::vector<Token> *m_tokens;
    std::uint64_t m_index{0};
};

class Lexer
{
public:
    Lexer() { tokens.reserve(4096); }

    TokenViewer tokenizeFile(const char *path)
    {
        std::ifstream ifs(path, std::ios::in);
        if (!ifs.is_open())
            throw std::runtime_error("Failed to open file");

        std::ostringstream ss;
        ss << ifs.rdbuf();
        m_source = ss.str();
        return tokenize(m_source);
    }

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

            // String
            if (source[offset] == '\"')
            {
                std::uint64_t len{1};
                while (offset + len < maxlen && source[offset + len] != '\"')
                    ++len;
                tokens.emplace_back(source, TokenKind::String, offset + 1,
                                    len - 1);
                offset += len + 1;
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

            // Bool
            if (source.substr(offset, 4) == "true")
            {
                tokens.emplace_back(source, TokenKind::Boolean, offset, 4);
                offset += 4;
                continue;
            }
            if (source.substr(offset, 5) == "false")
            {
                tokens.emplace_back(source, TokenKind::Boolean, offset, 5);
                offset += 5;
                continue;
            }

            // Null
            if (source.substr(offset, 4) == "null")
            {
                tokens.emplace_back(source, TokenKind::Null, offset, 4);
                offset += 4;
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
            case ':':
                kind = TokenKind::Colon;
                break;
            case ',':
                kind = TokenKind::Comma;
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
