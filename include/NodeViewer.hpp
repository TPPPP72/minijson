#pragma once

#include <Format.hpp>
#include <iostream>

class NodeViewer
{
public:
    void print(Node *node) { printNode(node, 0); }

private:
    void printList(Node *node, unsigned indent)
    {
        while (node)
        {
            printNode(node, indent);
            node = node->next;
        }
    }

    void printNode(Node *node, unsigned indent)
    {
        switch (node->kind)
        {
        case NodeKind::Object:
        case NodeKind::Array:
        {
            auto container_node = static_cast<ContainerNode *>(node);
            std::cout << formatContainerBegin(container_node, indent) << '\n';
            if (container_node->child)
                printList(container_node->child, indent + 2);
            std::cout << formatContainerEnd(container_node, indent) << '\n';
            break;
        }
        case NodeKind::Pair:
        {
            auto pair_node = static_cast<PairNode *>(node);
            std::cout << formatPairBegin(indent) << '\n';
            printNode(pair_node->key, indent + 2);
            printNode(pair_node->value, indent + 2);
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
