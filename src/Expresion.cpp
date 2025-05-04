#include "Expression.hpp"
#include <iostream>

namespace KLang{
    Expression::Expression(std::vector<Token> tokens){
        type = GENERIC;
        this->tokens = tokens;
    }
    Expression::Expression(){
        type = GENERIC;
        tokens = {};
    }
    ExprLiteral::ExprLiteral(Token t){
        tokens.push_back(t);
        type = LITERAL;
    }
    void Expression::Join(Expression other){
        for (int i = 0; i < other.tokens.size(); i ++){
            tokens.push_back(other.tokens[i]);
        }
    }
    void Expression::Print(){
        std::cout << "|";
        for (int i = 0; i < tokens.size(); i ++){
            std::cout << tokens[i].lexeme;
            if (i != tokens.size() - 1){
                std::cout << " ";
            }
        }
        std::cout << "|";

    }
}