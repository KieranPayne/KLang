#include "Parser.hpp"
namespace KLang{
    using namespace TreeNode;
    Parser::Parser(std::vector<Token> tokens){
        this->tokens = tokens;
        current = 0;
        expression()->Print();
    }

    Node* Parser::expression(){
        return equality();
    }
    Node* Parser::equality(){
        Node* node = comparison();
        while (Match({BANG_EQUAL,EQUAL_EQUAL})){
            Token op = Advance();
            Node* right = comparison();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::comparison(){
        Node* node = term();
        while (Match({LESS,LESS_EQUAL,GREATER,GREATER_EQUAL})){
            Token op = Advance();
            Node* right = term();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::term(){
        Node* node = factor();
        while (Match({PLUS,MINUS})){
            Token op = Advance();
            Node* right = factor();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::factor(){
        Node* node = unary();
        while (Match({STAR,SLASH})){
            Token op = Advance();
            Node* right = unary();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::unary(){
        if (Match({BANG,MINUS})){
            Token op = Advance();
            return new Unary(unary(),op);
        }else if (Check(LEFT_PAREN)){
            return grouping();
        }else{
            return primary();
        }
    }
    Node* Parser::grouping(){
        Consume(LEFT_PAREN,"expect left paren");
        Node* node = expression();
        Consume(RIGHT_PAREN,"expect right paren");
        return new Grouping(node);
    }
    Node* Parser::primary(){
        //todo: add func calls and variables
        return literal();
    }
    Node* Parser::literal(){
        return new Literal(Advance());
    }

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
    void Parser::Consume(TokenType type, std::string message){
        if (Check(type)){
            Advance();
        }else{
            //error handling goes here
        }
    }

}