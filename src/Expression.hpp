#pragma once
#include "Token.hpp"
#include <vector>
namespace KLang{
    enum ExpressionType{
        EXPR_BLANK,
        EXPR_GENERIC,
        EXPR_LITERAL,
        EXPR_IF,
        EXPR_WHILE,
        EXPR_FUNC_CALL,
        EXPR_ASSIGN,
        EXPR_LIST,
        EXPR_UNARY,
        EXPR_VARIABLE,
        EXPR_SEQUENCE,
        EXPR_PLACEHOLDER_OPERATOR,
        EXPR_ERROR
    };
    class Expression{
        public:
        ExpressionType type;
        std::vector<Token> tokens;
        Expression(std::vector<Token> tokens);
        Expression(ExpressionType type);
        Expression();
        void Join(Expression other);
        virtual void Print();
    };
    class ExprLiteral : public Expression{
        public:
        ExprLiteral(Token t);
        void Print();
    };
    class ExprIf : public Expression{
        public:
        Expression* trueBlock;
        Expression* falseBlock;
        Expression* condition;
        ExprIf(Expression* condition, Expression* trueBlock, Expression* falseBlock);
        void Print();
    };
    class ExprWhile : public Expression{
        public:
        Expression* condition;
        Expression* loopBlock;
        ExprWhile(Expression* condition, Expression* loopBlock);
        void Print();
    };
    class ExprFuncCall : public Expression{
        public:
        std::vector<Expression*> args;
        ExprFuncCall(Token name, std::vector<Expression*> args);
        void Print();
    };
    class ExprAssignment : public Expression{
        public:
        Expression* expr;
        ExprAssignment(Token name, Expression* expr);
        void Print();
    };
    //list of expressions
    class ExprList : public Expression{
        public:
        std::vector<Expression*> exprs;
        ExprList(std::vector<Expression*> exprs);
        void Print();
    };
    class ExprUnaryOp : public Expression{
        public:
        Expression* expr;
        ExprUnaryOp(Token op, Expression* expr);
        void Print();
    };
    class ExprVariable : public Expression{
        public:
        ExprVariable(Token name);
        void Print();
    };
    class ExprSequence : public Expression{
        public:
        std::vector<Expression*> exprs;
        ExprSequence(std::vector<Expression*> exprs);
        void Print();
    };
    
}