#pragma once
#include "Expression.hpp"
#include "Environment.hpp"
namespace KLang{
    class Interpreter{
        public:
        Expression* program;
        Environment env;
        Interpreter();
        Object* Run(Expression* program);
        void RunCommandLine();
        void RunCodeInFile(bool showTree);
    };
}