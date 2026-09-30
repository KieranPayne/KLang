#include "Token.hpp"
#include <iostream>

namespace KLang{
    Token::Token(TokenType tokenType, std::string lexeme, int line, int col){
        this->tokenType = tokenType;
        this->lexeme = lexeme;
        this->line = line;
        this->col = col;
    }
    void Token::Print(){
        std::cout << "TOKEN type:" << tokenType << " lexeme:" << lexeme << " line:" << line << " col:" << col << std::endl;
    }
    Token::Token(){
        
    }
};