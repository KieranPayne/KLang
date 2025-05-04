#include "Parser.hpp"
#include "Expression.hpp"
#include "Error.hpp"
namespace KLang{
    void Parser::Parse(std::vector<Token> tokens){
        Expression e(tokens);
        SplitExpression(e);
    }
    //splits expression into sub expressions based on binary operators
    std::vector<Expression> Parser::SplitExpression(Expression e){
        int index = 0;
        std::vector<Expression*> subExpressions;
        while (e.tokens[index].tokenType != ENDOFFILE){
            subExpressions.push_back(ReadExpression(e.tokens,index));
        }
        for (int i = 0; i < subExpressions.size(); i ++){
            subExpressions[i]->Print();
        }
        return {};
    }
    Expression* Parser::ReadExpression(std::vector<Token> tokens, int& index){
        TokenType type = tokens[index].tokenType;
        if (type == INTEGER || type == STRING || type == REAL){
            return new ExprLiteral(tokens[index++]);
        }
        // std::vector<TokenType> binOps = {PLUS,MINUS,SLASH,STAR,
        // GREATER,GREATER_EQUAL,LESS,LESS_EQUAL,EQUAL_EQUAL,BANG_EQUAL};

        //check for matching braces
        if (type == LEFT_PAREN || type == LEFT_BRACE || type == LEFT_SQUARE){
            TokenType open = type;
            TokenType closing = (type == LEFT_PAREN) ? RIGHT_PAREN : (type == LEFT_BRACE) ? RIGHT_BRACE : RIGHT_SQUARE;
            int count = 1;
            std::vector<Token> newTokens = {tokens[index]};
            index ++;
            while (count != 0) {
                if (index == tokens.size()){
                    Error::SyntaxError(newTokens[0].line,newTokens[0].col,"no closing brace found");
                    return new Expression(newTokens);
                }
                if (tokens[index].tokenType == open){
                    count ++;
                }else if (tokens[index].tokenType == closing){
                    count --;
                }
                newTokens.push_back(tokens[index]);
                index ++;
                
            }
            return new Expression(newTokens);
        }
        
    }
}