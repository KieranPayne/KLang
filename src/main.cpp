#include <iostream>
#include <fstream>
#include "Interpreter.hpp"
using namespace KLang;
int main(){
    // std::string textString = "print(\"hello world!\")";
    Interpreter i;
    i.RunCommandLine();
    return 0;
}