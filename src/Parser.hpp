#pragma once
#include <vector>
#include "Token.hpp"
#include "TreeNode.hpp"
namespace KLang{
    class Parser{
        public:
        int current = 0;
        std::vector<Token> tokens;
        Parser(std::vector<Token> tokens);
        private:
        Token Previous();
        Token Advance();
        Token Current();
        void Consume(TokenType type, std::string message);
        bool atEnd();
        bool Check(TokenType type);
        bool Match(std::vector<TokenType> types);
        TreeNode::Node* expression();
        TreeNode::Node* equality();
        TreeNode::Node* comparison();
        TreeNode::Node* term();
        TreeNode::Node* factor();
        TreeNode::Node* unary();
        TreeNode::Node* grouping();
        TreeNode::Node* primary();
        TreeNode::Node* literal();
    };
}