#include "Expression.hpp"
#include <iostream>

namespace KLang{
    Expression::Expression(ExpressionType type, std::vector<Token> tokens){
        this->type = type;
        this->tokens = tokens;
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