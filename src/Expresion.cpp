#include "Expression.hpp"
#include <iostream>

namespace KLang{
    Expression::Expression(std::vector<Token> tokens){
        type = GENERIC;
        this->tokens = tokens;
        if (tokens.size() == 0){
            type = BLANK;
        }
    }
    Expression::Expression(){
        type = GENERIC;
        tokens = {};
    }
    ExprLiteral::ExprLiteral(Token t){
        tokens.push_back(t);
        type = LITERAL;
    }
    ExprIf::ExprIf(Expression* condition, Expression* trueBlock, Expression* falseBlock){
        this->condition = condition;
        this->trueBlock = trueBlock;
        this->falseBlock = falseBlock;
    }
    ExprWhile::ExprWhile(Expression* condition, Expression* loopBlock){
        this->condition = condition;
        this->loopBlock = loopBlock;
    }
    void Expression::Join(Expression other){
        for (int i = 0; i < other.tokens.size(); i ++){
            tokens.push_back(other.tokens[i]);
        }
    }
    void Expression::Print(){
        std::cout << "|";
        for (int i = 0; i < tokens.size(); i ++){
            std::cout << tokens[i].lexeme;
            if (i != tokens.size() - 1){
                std::cout << " ";
            }
        }
        std::cout << "|";
    }
    void ExprIf::Print(){
        std::cout << "|";
        condition->Print();
        trueBlock->Print();
        falseBlock->Print();
        std::cout << "|";
    }
    void ExprWhile::Print(){
        std::cout << "|";
        condition->Print();
        loopBlock->Print();
        std::cout << "|";
    }
}