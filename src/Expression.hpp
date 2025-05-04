#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    enum ExpressionType{
        GENERIC,
        LITERAL
    };
    class Expression{
        public:
        ExpressionType type;
        std::vector<Token> tokens;
        Expression(std::vector<Token> tokens);
        Expression();
        virtual void Print();
    };
    class ExprLiteral : Expression{
        ExprLiteral(Token t);
    };
    
}