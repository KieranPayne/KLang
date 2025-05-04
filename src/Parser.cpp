#include "Parser.hpp"
#include "Expression.hpp"
#include "Error.hpp"
#include <iostream>
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
            Expression* expr = ReadExpression(e.tokens,index);
            if (expr == nullptr){
                std::cout << "stopping parsing: error reported" << std::endl;
                return {};
            }
            if (expr->type != EXPR_BLANK){
                subExpressions.push_back(expr);
            }
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
        //if statement
        else if (type == IF){
            if (index > (int)(tokens.size()) - 3){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected if statement");
                index ++;
                return nullptr;
            }
            index ++;
            Expression* condExp = ReadExpression(tokens,index);
            if (condExp->tokens[0].tokenType != LEFT_PAREN){
                Error::SyntaxError(condExp->tokens[0].line,condExp->tokens[0].col,"expected parenthesis after if");
                return nullptr;
            }
            Expression* trueExp = ReadExpression(tokens,index);
            Expression* falseExp = new Expression(std::vector<Token>{});
            if (index < tokens.size() && tokens[index].tokenType == ELSE){
                index ++;
                falseExp = ReadExpression(tokens,index);
            }
            return new ExprIf(condExp,trueExp,falseExp);
        //while loop
        }else if (type == WHILE){
            if (index > (int)(tokens.size()) - 3){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected while loop");
                index ++;
                return nullptr;
            }
            index ++;
            Expression* condition = ReadExpression(tokens,index);
            if (condition->tokens[0].tokenType != LEFT_PAREN){
                Error::SyntaxError(condition->tokens[0].line,condition->tokens[0].col,"expected parenthesis after while");
                return nullptr;
            }
            Expression* loopBlock = ReadExpression(tokens,index);
            return new ExprWhile(condition,loopBlock);
        //identifier (could be either variable or function)
        }else if (type == IDENTIFIER){
            if (tokens[index + 1].tokenType == ENDOFFILE){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected identifier");
                index ++;
                return nullptr;
            }
            //function call
            if (tokens[index + 1].tokenType == LEFT_PAREN){
                Token name = tokens[index];
                index += 2;
                std::vector<Expression*> exprs;
                std::vector<Expression*> currentArg;
                while (true){
                    if (tokens[index].tokenType == ENDOFFILE){
                        Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected closing parenthesis");
                        return nullptr;
                    }else if (tokens[index].tokenType == RIGHT_PAREN){
                        if (currentArg.size() == 1){
                            exprs.push_back(currentArg[0]);
                        }else if (currentArg.size() == 0){
                            exprs.push_back(new Expression(std::vector<Token>{}));
                        }else{
                            exprs.push_back(new ExprList(currentArg));
                        }
                        break;
                    }else if (tokens[index].tokenType == COMMA){
                        if (currentArg.size() == 1){
                            exprs.push_back(currentArg[0]);
                        }else if (currentArg.size() == 0){
                            exprs.push_back(new Expression(std::vector<Token>{}));
                        }else{
                            exprs.push_back(new ExprList(currentArg));
                        }
                        currentArg = {};
                        index ++;
                    }
                    currentArg.push_back(ReadExpression(tokens,index));
                }
                index ++;
                return new ExprFuncCall(name,exprs);
            //assignment
            }else if (tokens[index + 1].tokenType == EQUAL){
                Token name = tokens[index];
                index += 2;
                if (tokens[index].tokenType == ENDOFFILE){
                    Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected variable assignment");
                }
                std::vector<Expression*> expressions;
                while (true){
                    expressions.push_back(ReadExpression(tokens,index));
                    if (tokens[index].tokenType == ENDOFFILE){
                        Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected semicolon");
                    }
                    if (tokens[index].tokenType == SEMICOLON){
                        index ++;
                        break;
                    }
                }
                if (expressions.size() == 1){
                    return new ExprAssignment(name,expressions[0]);
                }else{
                    return new ExprAssignment(name, new ExprList(expressions));
                }
            }

        }
        
    }
}