#pragma once
#include "Expression.hpp"
#include "Environment.hpp"
namespace KLang{
    class Interpreter{
        public:
        Expression* program;
        Environment env;
        Interpreter(Expression* program);
        void Run();
    };
}