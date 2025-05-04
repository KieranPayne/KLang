#include "Parser.hpp"
#include "Expression.hpp"
#include "Error.hpp"
namespace KLang{
    void Parser::Parse(std::vector<Token> tokens){
        Expression e(tokens);
        SplitExpression(e);
    }
    //splits expression into sub expressions based on binary operators
    void Parser::SplitExpression(Expression e){
        int index = 0;
        std::vector<Expression> subExpressions;
        while (index < e.tokens.size()){
            subExpressions.push_back(ConsumeExpression(e.tokens,index));
            if (index < e.tokens.size()){
                subExpressions.push_back(Expression({e.tokens[index]}));
                index ++;
            }
        }
        for (int i = 0; i < subExpressions.size(); i ++){
            subExpressions[i].Print();
        }
    }
    //extracts the first expression found after the start index and returns it, also increments start index
    Expression Parser::ConsumeExpression(std::vector<Token> tokens, int& startIndex){
        std::vector<Token> newTokens;
        TokenType binaryOps[] = {
            PLUS,MINUS,SLASH,STAR,
            BANG_EQUAL, EQUAL_EQUAL, GREATER_EQUAL, LESS_EQUAL,
            LESS, GREATER
        };
        int numOps = 10;
        while (true){
            bool isOperator = false;
            if (startIndex == tokens.size()){
                isOperator = true;
            }else{
                for (int i = 0; i < numOps; i ++){
                    if (tokens[startIndex].tokenType == binaryOps[i]){
                        isOperator = true;
                        break;
                    }
                }
            }
            if (isOperator){
                if (newTokens.size() == 0){
                    std::string msg = "unexpected binary operator: ";
                    msg += tokens[startIndex].lexeme;
                    Error::SyntaxError(tokens[startIndex].line,tokens[startIndex].col,msg);
                    return Expression(std::vector<Token>{});
                }else{
                    return Expression(newTokens);
                }
            }else{
                newTokens.push_back(tokens[startIndex]);
            }
            startIndex ++;
        }
    }
}