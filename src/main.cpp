#include "PCH.hpp"
#include "Lexer.hpp"

int main(){
    std::ifstream file("test.B");
    std::string line;
    std::string data = "";
    while (std::getline(file,line)){
        data += line + "\n";
    }
    Lexer l;
    l.Tokenize(data);
    return 0;
}