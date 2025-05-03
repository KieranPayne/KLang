#pragma once
#include <string>
namespace KLang{
    enum TokenType{
        TEST
    };
    class Token{
        public:
        TokenType tokenType;
        std::string val;
        
        void Print();
        Token(TokenType tokenType, std::string val);
        
    };
    
}


