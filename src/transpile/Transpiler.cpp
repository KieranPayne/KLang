#include "Transpiler.hpp"
#include <fstream>
#include <iostream>
#include <memory>
namespace KLang{
    using namespace TreeNode;
    Transpiler::Transpiler(){
        tree = nullptr;
    }
    void Transpiler::GenerateCode(Node* tree, std::string path){
        std::string mainString = "int main(){\n";
        int currentIndentLevel = 1;
        Program* program = dynamic_cast<Program*>(tree);
        for (int i = 0; i < program->statements.size(); i ++){
            NodeType type = program->statements[i]->type;
            if (type != NODE_FUNC_DEC){
                AddIndent(mainString,currentIndentLevel);
                mainString += TranspileStatement(program->statements[i]);
                mainString += "\n";
            }
        }
        mainString += "}";
        std::ofstream file(path + "\\main.cpp");
        file << mainString;
        file.close();
    }
    std::string Transpiler::TranspileStatement(Node* statement){
        if (statement->type == NODE_EXPRSTMT){
            Node* expr = dynamic_cast<ExprStmt*>(statement)->expression;
            return TranspileStatement(expr) + ";";
        }else if (statement->type == NODE_LITERAL){
            return statement->tokens[0].lexeme;
        }else if (statement->type == NODE_VARIABLE){
            return statement->tokens[0].lexeme;
        }
        
    }
    void Transpiler::AddIndent(std::string& str, int level){
        for (int i = 0; i < level; i ++){
            str += '\t';
        }
    }
}