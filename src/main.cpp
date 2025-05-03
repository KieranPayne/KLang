#include <iostream>
#include "Scanner.hpp"
using namespace KLang;
int main(){
    std::string textString = "print(\"hello world!\")";
    std::vector<Token> tokens = Scanner::Scan(textString);
    for (int i = 0; i < tokens.size(); i ++){
        tokens[i].Print();
    }
    return 0;
}