#include "Parser.hpp"
namespace KLang{
    using namespace TreeNode;
    Parser::Parser(std::vector<Token> tokens){
        this->tokens = tokens;
        current = 0;
        Expression()->Print();
    }

    Node* Parser::Expression(){
        return Equality();
    }
    Node* Parser::Equality(){
        Node* node = Comparison();
        while (Match({BANG_EQUAL,EQUAL_EQUAL})){
            Token op = Advance();
            Node* right = Comparison();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::Comparison(){return new Node(NODE_NONE, {Advance()});}
    Node* Term(){}
    Node* Factor(){}
    Node* Unary(){}
    Node* Grouping(){}
    Node* Primary(){}
    Node* Literal(){}

    //helper functions
    Token Parser::Previous(){
        return tokens[current - 1];
    }
    Token Parser::Current(){
        return tokens[current];
    }
    Token Parser::Advance(){
        return tokens[current ++];
    }
    bool Parser::atEnd(){
        return Current().tokenType == EOF;
    }
    bool Parser::Check(TokenType type){
        return Current().tokenType == type;
    }
    bool Parser::Match(std::vector<TokenType> types){
        for (int i = 0; i < types.size(); i ++){
            if (Check(types[i])){
                return true;
            }
        }
        return false;
    }

}