#pragma once

#include <Token.hpp>

enum class NodeKind
{
    NoneKind,
    Object, // {...}
    Array,  // [...]
    Pair,   // key : value
    String,
    Number,
    Boolean,
    Null
};

struct Node
{
    NodeKind kind;
    Node *next{nullptr};
    Node(NodeKind k) : kind(k) {}
};

struct ContainerNode : Node
{
    const Token *begin{nullptr}, *end{nullptr};
    Node *child{nullptr};
    ContainerNode() : Node(NodeKind::NoneKind) {}
};

struct PairNode : Node
{
    Node *key{nullptr}, *value{nullptr};
    PairNode() : Node(NodeKind::Pair) {}
};

struct ValueNode : Node
{
    const Token *token;
    ValueNode(NodeKind k) : Node(k) {}
};
