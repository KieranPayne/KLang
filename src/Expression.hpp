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
        void Join(Expression other);
        virtual void Print();
    };
    class ExprLiteral : public Expression{
        public:
        ExprLiteral(Token t);
    };
    
}