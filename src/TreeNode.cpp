#include "TreeNode.hpp"
#include <iostream>
namespace KLang{
    namespace TreeNode{
        Node::Node(NodeType type, std::vector<Token> tokens){
            this->type = type;
            this->tokens = tokens;
        }
        Node::Node(){
            type = NODE_NONE;
        }
        Literal::Literal(Token token){
            tokens.push_back(token);
            type = NODE_LITERAL;
        }
        Binary::Binary(Node* lhs, Node* rhs, Token op){
            this->lhs = lhs;
            this->rhs = rhs;
            tokens.push_back(op);
        }
        Unary::Unary(Node* node, Token op){
            this->node = node;
            tokens.push_back(op);
        }
        Grouping::Grouping(Node* node){
            this->node = node;
        }
        Program::Program(std::vector<Node*> statements){
            this->statements = statements;
        }
        While::While(Node* condition, Node* block){
            this->condition = condition;
            this->block = block;
        }
        If::If(Node* condition, Node* trueBlock, Node* falseBlock){
            this->condition = condition;
            this->trueBlock = trueBlock;
            this->falseBlock = falseBlock;
        }
        void Node::Print(){
            std::cout << "[NODE";
            for (int i = 0; i < tokens.size(); i ++){
                std::cout << " " << tokens[i].lexeme;
            }
            std::cout << "]";
        }
        void Literal::Print(){
            std::cout << "(LITERAL ";
            std::cout << tokens[0].lexeme;
            std::cout << ")";
        }
        void Binary::Print(){
            std::cout << "[BINARY ";
            std::cout << tokens[0].lexeme;
            std::cout << " ";
            lhs->Print();
            rhs->Print();
            std::cout << "]";
        }
        void Unary::Print(){
            std::cout << "[UNARY ";
            std::cout << tokens[0].lexeme;
            std::cout << " ";
            node->Print();
            std::cout << "]";
        }
        void Grouping::Print(){
            std::cout << "{GROUPING ";
            node->Print();
            std::cout << "}";
        }
        void Program::Print(){
            std::cout << "[PROGRAM ";
            for (int i = 0; i < statements.size(); i ++){
                statements[i]->Print();
            }
            std::cout << "]";
        }
        void While::Print(){
            std::cout << "{WHILE ";
            condition->Print();
            block->Print();
            std::cout << "}";
        }
        void If::Print(){
            std::cout << "{WHILE ";
            condition->Print();
            trueBlock->Print();
            if (falseBlock != nullptr){
                falseBlock->Print();
            }
            std::cout << "}";
        }
    }
}