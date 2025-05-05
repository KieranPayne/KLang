#pragma once
#include "Token.hpp"
#include <vector>
#include "Environment.hpp"
#include "Object.hpp"
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
        EXPR_GROUPING,
        EXPR_BREAK,
        EXPR_CONTINUE,
        EXPR_RETURN,
        EXPR_BINARY,
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
        virtual Object* Evaluate(Environment& e);
        virtual void Print();
    };
    class ExprLiteral : public Expression{
        public:
        ExprLiteral(Token t);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprIf : public Expression{
        public:
        Expression* trueBlock;
        Expression* falseBlock;
        Expression* condition;
        ExprIf(Expression* condition, Expression* trueBlock, Expression* falseBlock);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprWhile : public Expression{
        public:
        Expression* condition;
        Expression* loopBlock;
        ExprWhile(Expression* condition, Expression* loopBlock);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprFuncCall : public Expression{
        public:
        std::vector<Expression*> args;
        ExprFuncCall(Token name, std::vector<Expression*> args);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprAssignment : public Expression{
        public:
        Expression* expr;
        ExprAssignment(Token name, Expression* expr);
        Object* Evaluate(Environment& e);
        void Print();
    };
    //list of expressions
    class ExprList : public Expression{
        public:
        std::vector<Expression*> exprs;
        ExprList(std::vector<Expression*> exprs);
        void CollectSubLists();
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
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprSequence : public Expression{
        public:
        std::vector<Expression*> exprs;
        ExprSequence(std::vector<Expression*> exprs);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprGrouping : public Expression{
        public:
        Expression* expr;
        ExprGrouping(Expression* expr);
        Object* Evaluate(Environment& e);
        void Print();
    };
    class ExprBreak : public Expression{
        public:
        ExprBreak(Token token);
        void Print();
    };
    class ExprContinue : public Expression{
        public:
        ExprContinue(Token token);
        void Print();
    };
    class ExprReturn : public Expression{
        public:
        Expression* returnVal;
        ExprReturn(Expression* returnVal);
        void Print();
    };
    class ExprBinaryOp : public Expression{
        public:
        Expression* lhs;
        Expression* rhs;
        ExprBinaryOp(Token op, Expression* lhs, Expression* rhs);
        Object* Evaluate(Environment& e);
        void Print();
    };
    
}