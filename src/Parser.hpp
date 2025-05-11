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
        bool atEnd();
        bool Check(TokenType type);
        bool Match(std::vector<TokenType> types);
        TreeNode::Node* Expression();
        TreeNode::Node* Equality();
        TreeNode::Node* Comparison();
        TreeNode::Node* Term();
        TreeNode::Node* Factor();
        TreeNode::Node* Unary();
        TreeNode::Node* Grouping();
        TreeNode::Node* Primary();
        TreeNode::Node* Literal();
    };
}