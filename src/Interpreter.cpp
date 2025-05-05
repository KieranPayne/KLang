#include "Interpreter.hpp"

namespace KLang{
    Interpreter::Interpreter(Expression* program){
        this->program = program;
        env = Environment();
    }
    void Interpreter::Run(){
        //evaluate first expression here
        program->Evaluate(env);
    }
}