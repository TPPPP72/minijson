#pragma once

#include <Lexer.hpp>
#include <Node.hpp>

class Parser
{
public:
    Parser(TokenViewer viewer) : tok(viewer) {}

    Node *parse()
    {
        if (tok.is(tok.lookAhead(1), TokenKind::Colon))
            return parsePair();
        return parseValue();
    }

private:
    Node *parsePair()
    {
        auto pair_node = new PairNode();

        auto key_node   = new ValueNode(NodeKind::String);
        key_node->token = tok.getToken();
        tok.skipToken();

        tok.consumeToken(TokenKind::Colon);

        pair_node->key   = key_node;
        pair_node->value = parseValue();
        return pair_node;
    }

    Node *parseValue()
    {
        ValueNode *val_node{nullptr};

        if (tok.is(TokenKind::Number))
            val_node = new ValueNode(NodeKind::Number);
        else if (tok.is(TokenKind::Boolean))
            val_node = new ValueNode(NodeKind::Boolean);
        else if (tok.is(TokenKind::Null))
            val_node = new ValueNode(NodeKind::Null);
        else if (tok.is(TokenKind::String))
            val_node = new ValueNode(NodeKind::String);

        val_node->token = tok.getToken();
        tok.skipToken();
        return val_node;
    }

private:
    TokenViewer tok;
};
