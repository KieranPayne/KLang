#include "Lexer.hpp"

namespace KLang{
    std::vector<Token> Lexer::Tokenize(std::string text){
        return std::vector<Token>{Token(TokenType::TEST,text)};
    }
};