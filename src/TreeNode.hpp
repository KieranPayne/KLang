#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    namespace TreeNode{
        enum NodeType {
            NODE_NONE,
            NODE_LITERAL
        };
        //base class of all other tree nodes.
        class Node{
            public:
            NodeType type;
            std::vector<Token> tokens;
            Node(NodeType type, std::vector<Token> tokens);
            Node();
            virtual void Print();
        };
        //strings, integers etc.
        class Literal : public Node{
            public:
            Literal(Token token);
            void Print();
        };
        class Binary : public Node{
            public:
            Node* lhs;
            Node* rhs;
            Binary(Node* lhs, Node* rhs, Token op);
            void Print();
        };
        class Unary : public Node{
            public:
            Node* node;
            Unary(Node* node, Token op);
            void Print();
        };
        class Grouping : public Node{
            public:
            Node* node;
            Grouping(Node* node);
            void Print();
        };
        class Program : public Node{
            public:
            std::vector<Node*> statements;
            Program(std::vector<Node*> statements);
            void Print();
        };
        class While : public Node{
            public:
            Node* condition;
            Node* block;
            While(Node* condition, Node* block);
            void Print();
        };
        class If : public Node{
            public:
            Node* condition;
            Node* trueBlock;
            Node* falseBlock;
            If(Node* condition, Node* trueBlock, Node* falseBlock);
            void Print();
        };

    }
}
