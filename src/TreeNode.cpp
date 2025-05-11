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
        void Node::Print(){
            std::cout << "[ NODE";
            for (int i = 0; i < tokens.size(); i ++){
                std::cout << " " << tokens[i].lexeme;
            }
            std::cout << "]";
        }
        void Literal::Print(){
            std::cout << "[ LITERAL ";
            std::cout << tokens[0].lexeme;
            std::cout << " ]";
        }
        void Binary::Print(){
            std::cout << "[ BINARY ";
            std::cout << tokens[0].lexeme;
            std::cout << " ";
            lhs->Print();
            rhs->Print();
            std::cout << " ]";
            
        }
    }
}