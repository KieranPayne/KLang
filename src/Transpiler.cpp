#include "Transpiler.hpp"
#include <fstream>
#include <iostream>
namespace KLang{
    using namespace TreeNode;
    Transpiler::Transpiler(){
        tree = nullptr;
    }
    void Transpiler::GenerateCode(Node* tree, std::string path){
        output = "";
        Program* program = dynamic_cast<Program*>(tree);
        for (int i = 0; i < program->statements.size(); i ++){
            if (program->statements[i]->type == NODE_FUNC_DEC){
                output += program->statements[i]->tokens[0].lexeme;
                output += "\n";
            }
        }
        std::ofstream file(path + "\\main.cpp");
        file << output;
        file.close();
    }
}