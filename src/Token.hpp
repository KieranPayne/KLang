#pragma once
#include <string>
namespace KLang{
    enum TokenType{
        TEST
    };
    class Token{
        public:
        TokenType tokenType;
        std::string lexeme;
        int line;
        
        void Print();
        Token(TokenType tokenType, std::string lexeme, int line);
        
    };
    
}


