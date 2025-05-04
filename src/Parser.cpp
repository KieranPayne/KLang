#include "Parser.hpp"
#include "Expression.hpp"
namespace KLang{
    void Parser::Parse(std::vector<Token> tokens){
        Expression e(ExpressionType::GENERIC, tokens);
        e.Print();
    }
}