#include "Expression.hpp"
#include <iostream>

namespace KLang{
    Expression::Expression(std::vector<Token> tokens){
        type = EXPR_GENERIC;
        this->tokens = tokens;
        if (tokens.size() == 0){
            type = EXPR_BLANK;
        }
    }
    Expression::Expression(){
        type = EXPR_GENERIC;
        tokens = {};
    }
    Expression::Expression(ExpressionType type){
        this->type = type;
        tokens = {};
    }
    ExprLiteral::ExprLiteral(Token t){
        tokens.push_back(t);
        type = EXPR_LITERAL;
    }
    ExprIf::ExprIf(Expression* condition, Expression* trueBlock, Expression* falseBlock){
        type = EXPR_IF;
        this->condition = condition;
        this->trueBlock = trueBlock;
        this->falseBlock = falseBlock;
    }
    ExprWhile::ExprWhile(Expression* condition, Expression* loopBlock){
        type = EXPR_WHILE;
        this->condition = condition;
        this->loopBlock = loopBlock;
    }
    ExprFuncCall::ExprFuncCall(Token name, std::vector<Expression*> args){
        type = EXPR_FUNC_CALL;
        tokens.push_back(name);
        this->args = args;
    }
    ExprAssignment::ExprAssignment(Token name, Expression* expr){
        tokens.push_back(name);
        this->expr = expr;
        type = EXPR_ASSIGN;
    }
    ExprList::ExprList(std::vector<Expression*> exprs){
        this->exprs = exprs;
        type = EXPR_LIST;
    }
    ExprUnaryOp::ExprUnaryOp(Token op, Expression* expr){
        tokens.push_back(op);
        this->expr = expr;
        type = EXPR_UNARY;
    }
    ExprVariable::ExprVariable(Token name){
        tokens.push_back(name);
        type = EXPR_VARIABLE;
    }
    ExprSequence::ExprSequence(std::vector<Expression*> exprs){
        this->exprs = exprs;
        type = EXPR_SEQUENCE;
    }
    ExprGrouping::ExprGrouping(Expression* expr){
        this->expr = expr;
        type = EXPR_GROUPING;
    }
    ExprBreak::ExprBreak(Token token){
        tokens.push_back(token);
        type = EXPR_BREAK;
    }
    ExprContinue::ExprContinue(Token token){
        tokens.push_back(token);
        type = EXPR_CONTINUE;
    }
    ExprReturn::ExprReturn(Expression* returnVal){
        this->returnVal = returnVal;
        type = EXPR_RETURN;
    }
    ExprBinaryOp::ExprBinaryOp(Token op, Expression* lhs, Expression* rhs){
        tokens.push_back(op);
        this->lhs = lhs;
        this->rhs = rhs;
        this->type = EXPR_BINARY;
    }
    void Expression::Join(Expression other){
        for (int i = 0; i < other.tokens.size(); i ++){
            tokens.push_back(other.tokens[i]);
        }
    }
    void ExprList::CollectSubLists(){
        std::vector<Expression*> newList;
        for (int i = 0; i < exprs.size(); i ++){
            if (exprs[i]->type == EXPR_LIST){
                ExprList* li = dynamic_cast<ExprList*>(exprs[i]);
                li->CollectSubLists();
                for (int j = 0; j < li->exprs.size(); j ++){
                    newList.push_back(li->exprs[j]);
                }
            }else{
                newList.push_back(exprs[i]);
            }
        }
        exprs = newList;
    }
    void Expression::Print(){
        std::cout << "[GENERIC ";
        for (int i = 0; i < tokens.size(); i ++){
            std::cout << tokens[i].lexeme;
            if (i != tokens.size() - 1){
                std::cout << " ";
            }
        }
        std::cout << "]";
    }
    void ExprLiteral::Print(){
        std::cout << "[";
        if (tokens[0].tokenType == INTEGER){
            std::cout << "INTEGER";
        }else if (tokens[0].tokenType == STRING){
            std::cout << "STRING";
        }else if (tokens[0].tokenType == REAL){
            std::cout << "REAL";
        }else if (tokens[0].tokenType == TRUE){
            std::cout << "BOOL";
        }else if (tokens[0].tokenType == FALSE){
            std::cout << "BOOL";
        }
        std::cout << " " << tokens[0].lexeme;
        std::cout << "]";
    }
    void ExprIf::Print(){
        std::cout << "[IF ";
        condition->Print();
        trueBlock->Print();
        falseBlock->Print();
        std::cout << "]";
    }
    void ExprWhile::Print(){
        std::cout << "[WHILE ";
        condition->Print();
        loopBlock->Print();
        std::cout << "]";
    }
    void ExprFuncCall::Print(){
        std::cout << "[FUNC CALL";
        std::cout << " " << tokens[0].lexeme << " ";
        for (int i = 0; i < args.size(); i ++){
            args[i]->Print();
        }
        std::cout << "]";
    }
    void ExprAssignment::Print(){
        std::cout << "[ASSIGN";
        std::cout << " " << tokens[0].lexeme << " ";
        expr->Print();
        std::cout << "]";
    }
    void ExprList::Print(){
        std::cout << "[LIST ";
        for (int i = 0; i < exprs.size(); i ++){
            exprs[i]->Print();
        }
        std::cout << "]";
    }
    void ExprUnaryOp::Print(){
        std::cout << "[UNARY ";
        std::cout << tokens[0].lexeme << " ";
        expr->Print();
        std::cout << "]";
    }
    void ExprVariable::Print(){
        std::cout << "[VARIABLE ";
        std::cout << tokens[0].lexeme;
        std::cout << "]";
    }
    void ExprSequence::Print(){
        std::cout << "[SEQUENCE ";
        for (int i = 0; i < exprs.size(); i ++){
            exprs[i]->Print();
        }
        std::cout << "]";
    }
    void ExprGrouping::Print(){
        std::cout << "[GROUPING ";
        expr->Print();
        std::cout << "]";
    }
    void ExprBreak::Print(){
        std::cout << "[BREAK]";
    }
    void ExprContinue::Print(){
        std::cout << "[CONTINUE]";
    }
    void ExprReturn::Print(){
        std::cout << "[RETURN ";
        returnVal->Print();
        std::cout << "]";
    }
    void ExprBinaryOp::Print(){
        std::cout << "[BIN OP ";
        std::cout << tokens[0].lexeme << " ";
        lhs->Print();
        rhs->Print();
        std::cout << "]";
    }
}