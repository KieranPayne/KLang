#pragma once
#include "Token.hpp"
#include "Expression.hpp"
#include <vector>
namespace KLang{
    class Parser{
        public:
        static void Parse(std::vector<Token> tokens);
        static void SplitExpression(Expression e);
        static Expression ConsumeExpression(std::vector<Token> tokens, int& startIndex);
    };
}