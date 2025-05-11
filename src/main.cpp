#include <iostream>
#include <fstream>
#include <vector>
#include "Token.hpp"
#include "Scanner.hpp"
int main(){
    std::ifstream file("testCode.klang");
    std::string line;
    std::string code = "";
    while (std::getline(file,line)){
        code += line;
        code += "\n";
    }
    std::vector<KLang::Token> tokens = KLang::Scanner::Scan(code);

    return 0;
}