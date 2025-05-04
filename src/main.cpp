#include <iostream>
#include <fstream>
#include "Scanner.hpp"
#include "Parser.hpp"
using namespace KLang;
int main(){
    // std::string textString = "print(\"hello world!\")";
    std::ifstream file("./testCode.klang");
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }  
    std::vector<Token> tokens = Scanner::Scan(file_contents);
    Parser::Parse(tokens);
    return 0;
}