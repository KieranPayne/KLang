#include <iostream>
#include "Lexer.hpp"
using namespace KLang;
int main(){
    std::string textString = "print(\"hello world!\")";
    std::vector<Token> tokens = Lexer::Tokenize(textString);
    for (int i = 0; i < tokens.size(); i ++){
        tokens[i].Print();
    }
    return 0;
}