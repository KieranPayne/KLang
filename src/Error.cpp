#include "Error.hpp"
#include <iostream>
namespace KLang{
    void Error::SyntaxError(int line, int col, std::string message){
        std::cout << "SYNTAX ERROR AT LINE " << (line + 1) << " COL " << (col+1) << "\nMSG:" << message << std::endl;
    }
    void Error::RunTimeError(std::string message){
        std::cout << "RUNTIME ERROR: " << message;
    }
}