#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    class Parser{
        public:
        static void Parse(std::vector<Token> tokens);
    };
}