#pragma once
#include <string>
namespace KLang{
    class Error{
        public:
        static void SyntaxError(int line, int col, std::string message);
        static void RunTimeError(std::string message);
    };
}