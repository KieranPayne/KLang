#pragma once
#include <vector>
#include "Token.hpp"
#include "TreeNode.hpp"
namespace KLang{
    class Error{
        public:
        bool sync;
        Token token;
        std::string message;
        Error(Token token, std::string message, bool sync);
    };
    class Parser{
        public:
        int current = 0;
        bool panicMode = false;
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
        void SkipStatement();
        TreeNode::Node* program(); //DONE
        TreeNode::Node* whileStmt(); //DONE
        TreeNode::Node* ifStmt(); //DONE
        TreeNode::Node* forStmt();
        TreeNode::Node* varDec();
        TreeNode::Node* funcDec();
        TreeNode::Node* classDec();
        TreeNode::Node* exprStmt();
        TreeNode::Node* returnStmt();
        TreeNode::Node* block();
        TreeNode::Node* statement(); //DONE
        TreeNode::Node* expression();
        TreeNode::Node* assignment();
        TreeNode::Node* call();
        TreeNode::Node* equality(); //DONE
        TreeNode::Node* comparison(); //DONE
        TreeNode::Node* term(); //DONE
        TreeNode::Node* factor(); //DONE
        TreeNode::Node* unary(); //DONE 
        TreeNode::Node* grouping(); //DONE
        TreeNode::Node* primary(); //DONE
        TreeNode::Node* literal(); //DONE
        void ReportError(Error e);
    };
    
}