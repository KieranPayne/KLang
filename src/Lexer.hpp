#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    class Lexer{
        public:
        static std::vector<Token> Tokenize(std::string text);
    };
}
