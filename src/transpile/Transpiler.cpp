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
        currentIndentLevel = 0;
        std::string mainString = "int main(){\n";
        std::string funcDefsString = "";
        Program* program = dynamic_cast<Program*>(tree);
        int mainIndent = 1;
        for (int i = 0; i < program->statements.size(); i ++){
            NodeType type = program->statements[i]->type;
            if (type != NODE_FUNC_DEC){
                int temp = currentIndentLevel;
                currentIndentLevel = mainIndent;
                AddIndent(mainString,currentIndentLevel);
                mainString += TranspileStatement(program->statements[i]);
                mainString += "\n";
                currentIndentLevel = temp;
            }else{
                funcDefsString += TranspileStatement(program->statements[i]);
                funcDefsString += "\n";
            }
        }
        currentIndentLevel = mainIndent;
        AddIndent(mainString,currentIndentLevel);
        mainString += "return 0;\n}";
        std::string headers = "#include \"KObject.hpp\"\nusing namespace KLang::KLangCompiled;";
        std::ofstream file(path + "\\main.cpp");
        file << headers << std::endl;
        file << funcDefsString << std::endl;
        file << mainString;
        file.close();
        std::cout << "done" << std::endl;
    }
    std::string Transpiler::TranspileStatement(Node* statement){
        if (statement->type == NODE_EXPRSTMT){
            Node* expr = dynamic_cast<ExprStmt*>(statement)->expression;
            return TranspileStatement(expr) + ";";
        }else if (statement->type == NODE_LITERAL){
            if (statement->tokens[0].tokenType == NULLVAL){
                return "std::shared_ptr<KObject>(new KObjNull())";
            }else if (statement->tokens[0].tokenType == STRING){
                return "KObjFromLiteral(\"" + statement->tokens[0].lexeme + "\")";
            }
            return "KObjFromLiteral(" + statement->tokens[0].lexeme + ")";
            // return statement->tokens[0].lexeme;
        }else if (statement->type == NODE_VARIABLE){
            return statement->tokens[0].lexeme;
        }else if (statement->type == NODE_BINARY){
            Binary* oper = dynamic_cast<Binary*>(statement);
            std::string operation = "";
            switch (oper->tokens[0].tokenType){
                case PLUS:
                operation = "OPERATOR_PLUS";
                break;
                case MINUS:
                operation = "OPERATOR_MINUS";
                break;
                case STAR:
                operation = "OPERATOR_MULTIPLY";
                break;
                case SLASH:
                operation = "OPERATOR_DIVIDE";
                break;
                case BANG_EQUAL:
                operation = "OPERATOR_NOTEEQUAL";
                break;
                case EQUAL_EQUAL:
                operation = "OPERATOR_EQUAL";
                break;
                case LESS_EQUAL:
                operation = "OPERATOR_LESSEQUAL";
                break;
                case LESS:
                operation = "OPERATOR_LESS";
                break;
                case GREATER:
                operation = "OPERATOR_GREATER";
                break;
                case GREATER_EQUAL:
                operation = "OPERATOR_GREATEREQUAL";
                break;
            }
            return TranspileStatement(oper->lhs) + "->Operation(" + TranspileStatement(oper->rhs) + "," + operation + ")";
        }else if (statement->type == NODE_VAR_DEC){
            VarDec* expr = dynamic_cast<VarDec*>(statement);
            std::string output = "std::shared_ptr<KObject> " + statement->tokens[0].lexeme;
            if (expr->expression != nullptr){
                output += " = ";
                output += TranspileStatement(expr->expression);
            }
            return output + ";";
        }else if (statement->type == NODE_CALL){
            Call* expr = dynamic_cast<Call*>(statement);
            std::string output = expr->tokens[0].lexeme;
            output += "(";
            for (int i = 0; i < expr->args.size(); i ++){
                output += TranspileStatement(expr->args[i]);
                if (i != expr->args.size() - 1){
                    output += ",";
                }
            }
            output += ")";
      

            return output;
        }else if (statement->type == NODE_FUNC_DEC){
            FuncDec* expr = dynamic_cast<FuncDec*>(statement);
            std::string output = "std::shared_ptr<KObject> ";
            output += expr->tokens[0].lexeme + "(";
            for (int i = 1; i < expr->tokens.size(); i ++ ){
                output += "std::shared_ptr<KObject> " + expr->tokens[i].lexeme;
                if (i != expr->tokens.size() - 1){
                    output += ",";
                }
            }
            output += "){\n";
            currentIndentLevel ++;
            Block* block = dynamic_cast<Block*>(expr->block);
            for (int i = 0; i < block->statements.size(); i ++){
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(block->statements[i]) + "\n";
            }
            //make sure it always returns null as default
            AddIndent(output,currentIndentLevel);
            output += "return std::shared_ptr<KObject>(new KObjNull());\n";
            output += "}";
            currentIndentLevel --;
            return output;

        }
        
    }
    void Transpiler::AddIndent(std::string& str, int level){
        for (int i = 0; i < level; i ++){
            str += '\t';
        }
    }
}