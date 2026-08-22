#pragma once

#include <Format.hpp>
#include <iostream>

class NodeViewer
{
public:
    void print(Node *node) { printNode(node, 0); }

private:
    void printNode(Node *node, unsigned indent)
    {
        switch (node->kind)
        {
        case NodeKind::Pair:
        {
            auto pair_node = static_cast<PairNode *>(node);
            std::cout << formatPairBegin(indent) << '\n';
            std::cout << formatValue(static_cast<ValueNode *>(pair_node->key),
                                     indent + 2)
                      << '\n';
            std::cout << formatValue(static_cast<ValueNode *>(pair_node->value),
                                     indent + 2)
                      << '\n';
            std::cout << formatPairEnd(indent) << '\n';
            break;
        }
        case NodeKind::Number:
        case NodeKind::Boolean:
        case NodeKind::String:
        case NodeKind::Null:
        {
            std::cout << formatValue(static_cast<ValueNode *>(node), indent)
                      << '\n';
            break;
        }
        default:
            std::cout << std::string(indent, ' ') << "<UnknownNode />\n";
            break;
        }
    }
};
