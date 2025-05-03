#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    class Scanner{
        public:
        static std::vector<Token> Scan(std::string text);
        static bool stringFound(std::string text, std::string str, int startIndex);
        static void SyntaxError(int line, std::string message);
    };
}
