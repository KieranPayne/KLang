#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    namespace TreeNode{
        enum NodeType {
            NODE_NONE,
            NODE_LITERAL,
            NODE_BINARY,
            NODE_UNARY,
            NODE_GROUPING,
            NODE_PROGRAM,
            NODE_WHILE,
            NODE_IF,
            NODE_FOR,
            NODE_VAR_DEC,
            NODE_FUNC_DEC,
            NODE_EXPRSTMT,
            NODE_RETURNSTMT,
            NODE_BLOCK,
            NODE_VARIABLE,
            NODE_ASSIGNMENT,
            NODE_CALL
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
        class For : public Node{
            public:
            Node* dec;
            Node* condition;
            Node* endOfLoop;
            Node* loopBlock;
            For(Node* dec, Node* condition, Node* endOfLoop, Node* loopBlock);
            void Print();
        };
        class VarDec : public Node{
            public:
            Node* expression;
            VarDec(Token name, Node* expression);
            void Print();
        };
        class FuncDec : public Node{
            public:
            //tokens will contain list of argument names
            Node* block;
            FuncDec(Token funcName, std::vector<Token> args, Node* block);
            void Print();
        };
        class ExprStmt : public Node{
            public:
            Node* expression;
            ExprStmt(Node* expression);
            void Print();
        };
        class ReturnStmt : public Node{
            public:
            Node* expression;
            ReturnStmt(Node* expression);
            void Print();
        };
        class Block : public Node{
            public:
            std::vector<Node*> statements;
            Block(std::vector<Node*> statements);
            void Print();
        };
        class Assignment : public Node{
            public:
            Node* expression;
            Assignment(Token name, Node* expression);
            void Print();
        };
        class Variable : public Node{
            public:
            Variable(Token name);
            void Print();
        };
        class Call : public Node{
            public:
            std::vector<Node*> args;
            Call(Token name, std::vector<Node*> args);
            void Print();
        };
    }
}
