#include "Token.hpp"
#include <iostream>

namespace KLang{
    Token::Token(TokenType tokenType, std::string val){
        this->tokenType = tokenType;
        this->val = val;
    }
    void Token::Print(){
        std::cout << "TOKEN type index: " << tokenType << " value: " << val << std::endl; 
    }
};