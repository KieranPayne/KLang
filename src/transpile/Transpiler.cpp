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
        //copy over required files
        std::vector<std::string> reqdFiles = {"..\\src\\transpile\\KObject.hpp","..\\src\\transpile\\KObject.cpp"};
        std::vector<std::string> outputNames = {"KObject.hpp","KObject.cpp"};
        for (int i = 0; i < reqdFiles.size(); i ++){
            std::ifstream file(reqdFiles[i]);
            std::string contents = "";
            std::string line;
            while (std::getline(file,line)){
                contents += line + "\n";
            } 
            file.close();
            std::ofstream output(path + "\\" + outputNames[i]);
            output << contents;
            output.close();
        }

        // std::string output = ""
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
        AddIndent(mainString,currentIndentLevel);
        mainString += "return 0;\n}";
        std::string headers = "#include \"KObject.hpp\"";
        std::ofstream file(path + "\\main.cpp");
        file << headers << std::endl;
        file << mainString;
        file.close();
        std::cout << "done" << std::endl;
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