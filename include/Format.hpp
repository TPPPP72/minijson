#pragma once

#include <Node.hpp>
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
    case TokenKind::Boolean:
        return "Boolean";
    case TokenKind::Null:
        return "Null";
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

inline const char *getNodeKindName(NodeKind kind)
{
    switch (kind)
    {
    case NodeKind::NoneKind:
        return "NoneKind";
    case NodeKind::Object:
        return "Object";
    case NodeKind::Array:
        return "Array";
    case NodeKind::Pair:
        return "Pair";
    case NodeKind::String:
        return "String";
    case NodeKind::Number:
        return "Number";
    case NodeKind::Boolean:
        return "Boolean";
    case NodeKind::Null:
        return "Null";
    }
    std::cerr << "getNodeKindName Error\n";
    std::exit(1);
}

// indent reserved for tree structure dumping
inline std::string formatValue(const ValueNode *node, unsigned indent)
{
    const char *name         = getNodeKindName(node->kind);
    std::string_view content = node->token->getContent();

    if (node->kind == NodeKind::String)
        return std::format("{}<{} value=\"{}\" />", std::string(indent, ' '),
                           name, content);
    else
        return std::format("{}<{} value='{}' />", std::string(indent, ' '),
                           name, content);
}

inline std::string formatContainerBegin(const ContainerNode *node,
                                        unsigned indent)
{
    const char *name = (node->kind == NodeKind::Object) ? "Object" : "Array";
    std::string_view begin = node->begin->getContent();
    return std::format("{}<{} '{}'>", std::string(indent, ' '), name, begin);
}

inline std::string formatContainerEnd(const ContainerNode *node,
                                      unsigned indent)
{
    const char *name = (node->kind == NodeKind::Object) ? "Object" : "Array";
    std::string_view end = node->end->getContent();
    return std::format("{}</{} '{}'>", std::string(indent, ' '), name, end);
}

inline std::string formatPairBegin(unsigned indent)
{
    return std::format("{}<Pair>", std::string(indent, ' '));
}

inline std::string formatPairEnd(unsigned indent)
{
    return std::format("{}</Pair>", std::string(indent, ' '));
}
