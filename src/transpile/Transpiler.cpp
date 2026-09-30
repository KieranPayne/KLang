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
        tree->Print();
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
        std::string headers = "#include \"KObject.hpp\"\n#include <iostream>\nusing namespace KLang::KLangCompiled;";
        std::string printFunc = "void print(KObject x){std::cout << *x.Cast(KOBJECT_STRING).strVal << std::endl;}";
        std::ofstream file(path + "\\main.cpp");
        file << headers << std::endl;
        file << printFunc << std::endl;
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
                return "KObject()";
            }else if (statement->tokens[0].tokenType == STRING){
                return "KObject(\"" + statement->tokens[0].lexeme + "\")";
            }
            return "KObject(" + statement->tokens[0].lexeme + ")";
            // return statement->tokens[0].lexeme;
        }else if (statement->type == NODE_VARIABLE){
            return statement->tokens[0].lexeme;
        }else if (statement->type == NODE_BINARY){
            Binary* oper = dynamic_cast<Binary*>(statement);
            std::string output = TranspileStatement(oper->lhs);
            TokenType op = oper->tokens[0].tokenType;
            switch ((int)op){
                case (int)PLUS:
                    output += ".Arithmetic(" + TranspileStatement(oper->rhs) + ",OPERATOR_PLUS)";
                    break;
                case (int)MINUS:
                    output += ".Arithmetic(" + TranspileStatement(oper->rhs) + ",OPERATOR_MINUS)";
                    break;
                case (int)STAR:
                    output += ".Arithmetic(" + TranspileStatement(oper->rhs) + ",OPERATOR_STAR)";
                    break;
                case (int)SLASH:
                    output += ".Arithmetic(" + TranspileStatement(oper->rhs) + ",OPERATOR_SLASH)";
                    break;
                case (int)EQUAL_EQUAL:
                    output += ".Equality(" + TranspileStatement(oper->rhs) + ",true)";
                    break;
                case (int)BANG_EQUAL:
                    output += ".Equality(" + TranspileStatement(oper->rhs) + ",false)";
                    break;
                case (int)GREATER:
                    output += ".Comparison(" + TranspileStatement(oper->rhs) + ",OPERATOR_GREATER)";
                    break;
                case (int)GREATER_EQUAL:
                    output += ".Comparison(" + TranspileStatement(oper->rhs) + ",OPERATOR_GREATEREQUAL)";
                    break;
                case (int)LESS:
                    output += ".Comparison(" + TranspileStatement(oper->rhs) + ",OPERATOR_LESS)";
                    break;
                case (int)LESS_EQUAL:
                    output += ".Comparison(" + TranspileStatement(oper->rhs) + ",OPERATOR_LESSEQUAL)";
                    break;
            }
            return output;
        }else if (statement->type == NODE_VAR_DEC){
            VarDec* expr = dynamic_cast<VarDec*>(statement);
            std::string output = "KObject " + statement->tokens[0].lexeme;
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
            std::string output = "KObject ";
            output += expr->tokens[0].lexeme + "(";
            for (int i = 1; i < expr->tokens.size(); i ++ ){
                output += "KObject " + expr->tokens[i].lexeme;
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
            output += "return KObject();\n";
            output += "}";
            currentIndentLevel --;
            return output;

        }else if (statement->type == NODE_GROUPING){
            Grouping* expr = dynamic_cast<Grouping*>(statement);
            return "(" + TranspileStatement(expr->node) + ")";
        }else if (statement->type == NODE_UNARY){
            Unary* expr = dynamic_cast<Unary*>(statement);
            std::string op;
            if (expr->tokens[0].tokenType == MINUS){
                op = "OPERATOR_MINUS";
            }else if (expr->tokens[0].tokenType == BANG){
                op = "OPERATOR_NEGATE";
            }
            return TranspileStatement(expr->node) + ".UnaryOp(" + op + ")";
        }else if (statement->type == NODE_WHILE){
            While* expr = dynamic_cast<While*>(statement);
            std::string output = "while (";
            output += TranspileStatement(expr->condition);
            output += ".AsBool())\n";
            if (expr->block->type != NODE_BLOCK){
                currentIndentLevel ++;
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->block);
                currentIndentLevel --;
            }else{
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->block);
            }
            return output;
        }else if (statement->type == NODE_BLOCK){
            Block* expr = dynamic_cast<Block*>(statement);
            std::string output = "{\n";
            currentIndentLevel ++;
            for (int i = 0; i < expr->statements.size(); i ++){
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->statements[i]);
                output += "\n";
            }
            currentIndentLevel --;

            AddIndent(output,currentIndentLevel);
            output += "}";
            return output;
        }else if (statement->type == NODE_IF){
            If* expr = dynamic_cast<If*>(statement);
            std::string output = "if (";
            output += TranspileStatement(expr->condition);
            output += ".AsBool())\n";
            if (expr->trueBlock->type != NODE_BLOCK){
                currentIndentLevel ++;
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->trueBlock);
                currentIndentLevel --;
            }else{
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->trueBlock);
            }
            if (expr->falseBlock != nullptr){
                if (expr->trueBlock->type != NODE_BLOCK){
                    output += "\n";
                    AddIndent(output,currentIndentLevel);
                }
                output += "else";
                if (expr->falseBlock->type != NODE_BLOCK){
                    output += "\n";
                    currentIndentLevel ++;
                    AddIndent(output,currentIndentLevel);
                    output += TranspileStatement(expr->falseBlock);
                    currentIndentLevel --;
                }else{
                    output += TranspileStatement(expr->falseBlock);
                }
            }
            return output;
        }else if (statement->type == NODE_FOR){
            For* expr = dynamic_cast<For*>(statement);
            std::string output = "for (";
            output += TranspileStatement(expr->dec);
            output += TranspileStatement(expr->condition) + ".AsBool();";
            output += TranspileStatement(expr->endOfLoop);
            output += ")\n";
            if (expr->loopBlock->type != NODE_BLOCK){
                AddIndent(output,++currentIndentLevel);
                output += TranspileStatement(expr->loopBlock);
                currentIndentLevel--;
            }else{
                AddIndent(output,currentIndentLevel);
                output += TranspileStatement(expr->loopBlock);
            }
            return output;
        }else if (statement->type == NODE_ASSIGNMENT){
            Assignment* expr = dynamic_cast<Assignment*>(statement);
            std::string output = expr->tokens[0].lexeme + " = ";
            output += TranspileStatement(expr->expression);
            return output;
        }else if (statement->type == NODE_RETURNSTMT){
            ReturnStmt* expr = dynamic_cast<ReturnStmt*>(statement);
            std::string output = "return";
            if (expr->expression != nullptr){
                output += " " + TranspileStatement(expr->expression);
            }
            output += ";";
            return output;
        }
    }
    void Transpiler::AddIndent(std::string& str, int level){
        for (int i = 0; i < level; i ++){
            str += '\t';
        }
    }
}