#pragma once

#include <Lexer.hpp>
#include <Node.hpp>

class Parser
{
public:
    Parser(TokenViewer viewer) : tok(viewer) {}

    Node *parse()
    {
        if (tok.is(TokenKind::LeftBracket) || tok.is(TokenKind::LeftBrace))
            return parseContainer();
        else if (tok.is(tok.lookAhead(1), TokenKind::Colon))
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
        if (tok.is(TokenKind::LeftBracket) || tok.is(TokenKind::LeftBrace))
            return parseContainer();

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

    Node *parseContainer()
    {
        auto container_node   = new ContainerNode();
        container_node->begin = tok.getToken();

        TokenKind end_pair = TokenKind::NoneKind;

        if (tok.tryConsumeToken(TokenKind::LeftBracket))
        {
            container_node->kind = NodeKind::Array;
            end_pair             = TokenKind::RightBracket;
        }
        else if (tok.tryConsumeToken(TokenKind::LeftBrace))
        {
            container_node->kind = NodeKind::Object;
            end_pair             = TokenKind::RightBrace;
        }

        Node *tail{nullptr};
        while (!tok.tryConsumeToken(end_pair))
        {
            if (tok.is(TokenKind::Comma))
                tok.skipToken();

            Node *new_node;
            if (end_pair == TokenKind::RightBrace)
                new_node = parsePair();
            else
                new_node = parseValue();

            if (!container_node->child)
                container_node->child = new_node;
            else
                tail->next = new_node;
            tail = new_node;
        }

        container_node->end = tok.lookBack(1);
        return container_node;
    }

private:
    TokenViewer tok;
};
