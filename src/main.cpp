#include <iostream>
#include <fstream>
#include "Scanner.hpp"
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
    for (int i = 0; i < tokens.size(); i ++){
        tokens[i].Print();
    }
    return 0;
}