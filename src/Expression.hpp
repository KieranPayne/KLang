#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    enum ExpressionType{
        GENERIC
    };
    class Expression{
        public:
        ExpressionType type;
        std::vector<Token> tokens;
        Expression(ExpressionType type,std::vector<Token> tokens);
        virtual void Print();
    };
    
}