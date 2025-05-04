#pragma once
#include "Token.hpp"
#include "Expression.hpp"
#include <vector>
namespace KLang{
    class Parser{
        public:
        static void Parse(std::vector<Token> tokens);
        static Expression* CheckForBinOp(std::vector<Token> tokens, int& index, Expression* start);
        static ExprSequence* ParseToSequence(std::vector<Token> tokens);
        static Expression* ReadExpression(std::vector<Token> tokens, int& index);
        static Expression* ApplyUnaryTo(Expression* expr, Token op);
    };
}