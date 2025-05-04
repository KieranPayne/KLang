#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    enum ExpressionType{
        BLANK,
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
    class ExprIf : public Expression{
        public:
        Expression trueBlock;
        Expression falseBlock;
        Expression condition;
        ExprIf(Expression condition, Expression trueBlock, Expression falseBlock);
        void Print();
    };
    
}