#include "Token.hpp"
#include <iostream>

namespace KLang{
    Token::Token(TokenType tokenType, std::string lexeme, int line){
        this->tokenType = tokenType;
        this->lexeme = lexeme;
        this->line = line;
    }
    void Token::Print(){
        std::cout << "TOKEN type:" << tokenType << " lexeme:" << lexeme << " line:" << line << std::endl;
    }
};