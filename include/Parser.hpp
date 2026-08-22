#pragma once

#include <Lexer.hpp>
#include <Node.hpp>

class Parser
{
public:
    Parser(TokenViewer viewer) : tok(viewer) {}

    Node *parse() { return parseValue(); }

private:
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
