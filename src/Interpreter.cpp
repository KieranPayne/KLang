#include "Interpreter.hpp"

namespace KLang{
    Interpreter::Interpreter(){
        // this->program = program;
        env = Environment();
    }
    void Interpreter::Run(Expression* program){
        this->program = program;
        //evaluate first expression here
        this->program->Evaluate(env);
    }
}