#include <iostream>
#include <fstream>
#include <vector>
#include "Token.hpp"
#include "Scanner.hpp"
#include "Parser.hpp"
#include "TreeNode.hpp"
#include "transpile/Transpiler.hpp"
int main(){
    std::ifstream file("testCode.klang");
    std::string line;
    std::string code = "";
    while (std::getline(file,line)){
        code += line;
        code += "\n";
    }
    std::vector<KLang::Token> tokens = KLang::Scanner::Scan(code);
    KLang::Parser p(tokens);
    KLang::TreeNode::Node* node = p.Parse();
    KLang::Transpiler t;
    t.GenerateCode(node, "..\\transpile_output");
    return 0;
}