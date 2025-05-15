#include "TreeNode.hpp"
#include <iostream>
namespace KLang{
    namespace TreeNode{
        Node::Node(NodeType type, std::vector<Token> tokens){
            this->type = type;
            this->tokens = tokens;
        }
        Node::Node(){
            type = NODE_NONE;
        }
        Literal::Literal(Token token){
            tokens.push_back(token);
            type = NODE_LITERAL;
        }
        Binary::Binary(Node* lhs, Node* rhs, Token op){
            type = NODE_BINARY;
            this->lhs = lhs;
            this->rhs = rhs;
            tokens.push_back(op);
        }
        Unary::Unary(Node* node, Token op){
            type = NODE_UNARY;
            this->node = node;
            tokens.push_back(op);
        }
        Grouping::Grouping(Node* node){
            this->node = node;
            type = NODE_GROUPING;
        }
        Program::Program(std::vector<Node*> statements){
            this->statements = statements;
            type = NODE_PROGRAM;
        }
        While::While(Node* condition, Node* block){
            this->condition = condition;
            this->block = block;
            type = NODE_WHILE;
        }
        If::If(Node* condition, Node* trueBlock, Node* falseBlock){
            this->condition = condition;
            this->trueBlock = trueBlock;
            this->falseBlock = falseBlock;
            type = NODE_IF;
        }
        For::For(Node* dec, Node* condition, Node* endOfLoop, Node* loopBlock){
            this->dec = dec;
            this->condition = condition;
            this->endOfLoop = endOfLoop;
            this->loopBlock = loopBlock;
            type = NODE_FOR;
        }
        VarDec::VarDec(Token name, Node* expression){
            tokens.push_back(name);
            this->expression = expression;
            type = NODE_VAR_DEC;
        }
        FuncDec::FuncDec(Token funcName, std::vector<Token> args, Node* block){
            tokens = args;
            tokens.insert(tokens.begin(),funcName);
            this->block = block;
            type = NODE_FUNC_DEC;
        }
        ExprStmt::ExprStmt(Node* expression){
            this->expression = expression;
            type = NODE_EXPRSTMT;
        }
        ReturnStmt::ReturnStmt(Node* expression){
            this->expression = expression;
            type = NODE_RETURNSTMT;
        }
        Block::Block(std::vector<Node*> statements){
            this->statements = statements;
            type = NODE_BLOCK;
        }
        Assignment::Assignment(Token name, Node* expression){
            tokens.push_back(name);
            this->expression = expression;
            type = NODE_ASSIGNMENT;
        }
        Variable::Variable(Token name){
            tokens.push_back(name);
            type = NODE_VARIABLE;
        }
        Call::Call(Token name, std::vector<Node*> args){
            tokens.push_back(name);
            this->args = args;
            type = NODE_CALL;
        }
        void Node::Print(){
            std::cout << "[NODE";
            for (int i = 0; i < tokens.size(); i ++){
                std::cout << " " << tokens[i].lexeme;
            }
            std::cout << "]";
        }
        void Literal::Print(){
            std::cout << "(LITERAL ";
            std::cout << tokens[0].lexeme;
            std::cout << ")";
        }
        void Binary::Print(){
            std::cout << "[BINARY ";
            std::cout << tokens[0].lexeme;
            std::cout << " ";
            lhs->Print();
            rhs->Print();
            std::cout << "]";
        }
        void Unary::Print(){
            std::cout << "[UNARY ";
            std::cout << tokens[0].lexeme;
            std::cout << " ";
            node->Print();
            std::cout << "]";
        }
        void Grouping::Print(){
            std::cout << "{GROUPING ";
            node->Print();
            std::cout << "}";
        }
        void Program::Print(){
            std::cout << "[PROGRAM ";
            for (int i = 0; i < statements.size(); i ++){
                statements[i]->Print();
            }
            std::cout << "]";
        }
        void While::Print(){
            std::cout << "{WHILE ";
            condition->Print();
            block->Print();
            std::cout << "}";
        }
        void If::Print(){
            std::cout << "{WHILE ";
            condition->Print();
            trueBlock->Print();
            if (falseBlock != nullptr){
                falseBlock->Print();
            }
            std::cout << "}";
        }
        void For::Print(){
            std::cout << "{FOR ";
            dec->Print();
            condition->Print();
            endOfLoop->Print();
            loopBlock->Print();
            std::cout << "}";
        }
        void VarDec::Print(){
            std::cout << "[VARDEC ";
            std::cout << tokens[0].lexeme;
            if (expression != nullptr){
                expression->Print();
            }
            std::cout << "]";
        }
        void FuncDec::Print(){
            std::cout << "[FUNCDEC ";
            for (int i = 0; i < tokens.size(); i ++){
                std::cout << tokens[i].lexeme << " ";
            }
            block->Print();
            std::cout << "]";
        }
        void ExprStmt::Print(){
            std::cout << "{EXPRSTMT ";
            expression->Print();
            std::cout << "}";
        }
        void ReturnStmt::Print(){
            std::cout << "[RETURN ";
            if (expression != nullptr){
                expression->Print();
            }
            std::cout << "]";
        }
        void Block::Print(){
            std::cout << "{BLOCK ";
            for (int i = 0; i < statements.size(); i ++){
                statements[i]->Print();
            }
            std::cout << "}";
        }
        void Assignment::Print(){
            std::cout << "[ASSIGN ";
            std::cout << tokens[0].lexeme;
            expression->Print();
            std::cout << "]";
        }
        void Variable::Print(){
            std::cout << "(VARIABLE ";
            std::cout << tokens[0].lexeme << ")";
        }
        void Call::Print(){
            std::cout << "[CALL ";
            std::cout << tokens[0].lexeme;
            for (int i = 0; i < args.size(); i ++){
                args[i]->Print();
            }
            std::cout << "]";
        }
    }

}