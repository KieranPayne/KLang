#include "Interpreter.hpp"
#include <iostream>
#include <fstream>
#include "Scanner.hpp"
#include "Parser.hpp"
namespace KLang{
    Interpreter::Interpreter(){
        env = Environment();
    }
    Object* Interpreter::Run(Expression* program){
        this->program = program;
        return this->program->Evaluate(env);

    }
    void Interpreter::RunCommandLine(){
        std::cout << "starting command line input" << std::endl;
        std::cout << "Show tree? (y/n): " << std::endl;
        std::string line;
        std::getline(std::cin,line);
        bool showTree = false;
        if (line == "y"){
            showTree = true;
        }
        while (true){
            std::cout << ">>";
            std::string line;
            std::getline(std::cin,line);
            if (line == "end"){
                break;
            }else if (line == "refresh"){
                RunCodeInFile();
                continue;
            }
            std::vector<Token> tokens = Scanner::Scan(line);
            ExprSequence* seq = Parser::ParseToSequence(tokens);
            if (showTree){
                for (int i = 0; i < seq->exprs.size(); i ++){
                    seq->exprs[i]->Print();
                    std::cout << std::endl;
                }
            }
            Object* result = Run(seq);
            std::cout << std::endl;
            std::cout << ">>";
            result->Print();
            if (!result->variableVal){
                delete result;
            }

            std::cout << std::endl;
            
        }
    }
    void Interpreter::RunCodeInFile()
    {    
        std::ifstream file("./testCode.klang");
        std::string str;
        std::string file_contents;
        while (std::getline(file, str))
        {
            file_contents += str;
            file_contents.push_back('\n');
        }  
        std::vector<Token> tokens = Scanner::Scan(file_contents);
        Object* result = Run(Parser::Parse(tokens));
        if (!result->variableVal){
            delete result;
        }
        std::cout << std::endl;
    }
}