#pragma once
#include "Token.hpp"
#include "Expression.hpp"
#include <vector>
namespace KLang{
    class Parser{
        public:
        static void Parse(std::vector<Token> tokens);
        static std::vector<Expression> SplitExpression(Expression e);
        static Expression* ReadExpression(std::vector<Token> tokens, int& index);
        static Expression* ApplyUnaryTo(Expression* expr, Token op);
    };
}