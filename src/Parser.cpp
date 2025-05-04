#include "Parser.hpp"
#include "Expression.hpp"
#include "Error.hpp"
#include <iostream>
namespace KLang{
    void Parser::Parse(std::vector<Token> tokens){
        ExprSequence* seq = ParseToSequence(tokens);
        for (int i = 0; i < seq->exprs.size(); i ++){
            seq->exprs[i]->Print();
            std::cout << std::endl;
        }
        std:: cout << std::endl;
    }
    //splits expression into sub expressions based on binary operators
    ExprSequence* Parser::ParseToSequence(std::vector<Token> tokens){
        int index = 0;
        if (tokens[tokens.size()-1].tokenType != ENDOFFILE){
            tokens.push_back(Token(ENDOFFILE,"",0,0));
        }
        std::vector<Expression*> subExpressions;
        while (tokens[index].tokenType != ENDOFFILE){
            if (tokens[index].tokenType == SEMICOLON){
                index ++;
                continue;
            }
            Expression* expr = ReadExpression(tokens,index);
            if (expr->type == EXPR_ERROR){
                std::cout << "stopping parsing: error reported" << std::endl;
                break;
            }
            if (expr->type != EXPR_BLANK){
                subExpressions.push_back(expr);
            }
        }
        ExprSequence* seq = new ExprSequence(subExpressions);
        return seq;
    }
    Expression* Parser::ApplyUnaryTo(Expression* expr, Token op){
        if (expr->type == EXPR_LIST){
            ExprList* li = dynamic_cast<ExprList*>(expr);
            li->exprs[0] = ApplyUnaryTo(li->exprs[0],op);
            return li;
        }else{
            ExprUnaryOp* unary = new ExprUnaryOp(op,expr);
            return unary;
        }
        return nullptr;
    }
    Expression* Parser::ReadExpression(std::vector<Token> tokens, int& index){
        TokenType type = tokens[index].tokenType;
        if (type == BANG || type == MINUS){
            Token op = tokens[index];
            index ++;
            Expression* expr = ReadExpression(tokens,index);
            if (expr->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            expr = ApplyUnaryTo(expr,op);
            return expr;
        }
        if (type == INTEGER || type == STRING || type == REAL){
            if (tokens[index + 1].tokenType != ENDOFFILE){
                //check for binary operator here, if there is one turn whole thing into expression list
                TokenType type = tokens[index + 1].tokenType;
                std::vector<TokenType> operators = {PLUS,MINUS,SLASH,STAR,
                EQUAL_EQUAL,GREATER_EQUAL,LESS_EQUAL,LESS,GREATER};
                bool isOp = false;
                for (int i = 0; i < operators.size(); i ++){
                    if (operators[i] == type){
                        isOp = true;
                        break;
                    }
                }
                if (isOp){
                    std::vector<Expression*> exprs = {new ExprLiteral(tokens[index])};
                    index ++;
                    Expression* operation = new Expression({tokens[index]});
                    operation->type = EXPR_PLACEHOLDER_OPERATOR;
                    exprs.push_back(operation);
                    index ++;
                    Expression* otherSide = ReadExpression(tokens,index);
                    if (otherSide->type == EXPR_ERROR){
                        return new Expression(EXPR_ERROR);
                    }
                    if (otherSide->type == EXPR_LIST){
                        ExprList* li = dynamic_cast<ExprList*>(otherSide);
                        for (int i = 0; i < li->exprs.size(); i ++){
                            exprs.push_back(li->exprs[i]);
                        }
                    }else{
                        exprs.push_back(otherSide);
                    }
                    return new ExprList(exprs);
                }
            }
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
                    return new Expression(EXPR_ERROR);
                }
                if (tokens[index].tokenType == open){
                    count ++;
                }else if (tokens[index].tokenType == closing){
                    count --;
                }
                newTokens.push_back(tokens[index]);
                index ++;
            }
            if (type == LEFT_BRACE){
                newTokens.erase(newTokens.begin());
                newTokens.erase(newTokens.end()-1);
            }
            return new Expression(newTokens);
        }
        //if statement
        else if (type == IF){
            if (index > (int)(tokens.size()) - 3){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected if statement");
                return new Expression(EXPR_ERROR);
            }
            index ++;
            Expression* condExp = ReadExpression(tokens,index);
            if (condExp->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            if (condExp->tokens[0].tokenType != LEFT_PAREN){
                Error::SyntaxError(condExp->tokens[0].line,condExp->tokens[0].col,"expected parenthesis after if");
                return new Expression(EXPR_ERROR);
            }
            Expression* trueExp = ReadExpression(tokens,index);
            if (trueExp->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            trueExp = ParseToSequence(trueExp->tokens);
            if (trueExp->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            ExprSequence* seq = dynamic_cast<ExprSequence*>(trueExp);
            if (seq->exprs.size() == 1){
                trueExp = seq->exprs[0];
            }
            Expression* falseExp = new Expression(std::vector<Token>{});
            if (index < tokens.size() && tokens[index].tokenType == ELSE){
                index ++;
                falseExp = ReadExpression(tokens,index);
                if (falseExp->type == EXPR_ERROR){
                    return new Expression(EXPR_ERROR);
                }
                falseExp = ParseToSequence(falseExp->tokens);
                if (falseExp->type == EXPR_ERROR){
                    return new Expression(EXPR_ERROR);
                }
                ExprSequence* seq = dynamic_cast<ExprSequence*>(falseExp);
                if (seq->exprs.size() == 1){
                    falseExp = seq->exprs[0];
                }
            }
            return new ExprIf(condExp,trueExp,falseExp);
        //while loop
        }else if (type == WHILE){
            if (index > (int)(tokens.size()) - 3){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected while loop");
                return new Expression(EXPR_ERROR);
            }
            index ++;
            Expression* condition = ReadExpression(tokens,index);
            if (condition->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            if (condition->tokens[0].tokenType != LEFT_PAREN){
                Error::SyntaxError(condition->tokens[0].line,condition->tokens[0].col,"expected parenthesis after while");
                return new Expression(EXPR_ERROR);
            }
            Expression* loopBlock = ReadExpression(tokens,index);
            if (loopBlock->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            loopBlock = ParseToSequence(loopBlock->tokens);
            if (loopBlock->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            ExprSequence* seq = dynamic_cast<ExprSequence*>(loopBlock);
            if (seq->exprs.size() == 1){
                loopBlock = seq->exprs[0];
            }
            if (loopBlock->type == EXPR_ERROR){
                return new Expression(EXPR_ERROR);
            }
            return new ExprWhile(condition,loopBlock);
        //identifier (could be either variable or function)
        }else if (type == IDENTIFIER){
            if (tokens[index + 1].tokenType == ENDOFFILE){
                Error::SyntaxError(tokens[index].line,tokens[index].col,"unexpected identifier");
                index ++;
                return new Expression(EXPR_ERROR);

            }
            //function call
            if (tokens[index + 1].tokenType == LEFT_PAREN){
                Token name = tokens[index];
                index += 2;
                std::vector<Expression*> exprs;
                while (true){
                    if (tokens[index].tokenType == ENDOFFILE){
                        Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected closing parenthesis");
                        return new Expression(EXPR_ERROR);

                    }else if (tokens[index].tokenType == RIGHT_PAREN){
                        break;
                    }else if (tokens[index].tokenType == COMMA){
                        index ++;
                    }
                    exprs.push_back(ReadExpression(tokens,index));
                    if (exprs[exprs.size()-1]->type == EXPR_ERROR){
                        return new Expression(EXPR_ERROR);
                    }
                }
                index ++;
                return new ExprFuncCall(name,exprs);
            //assignment
            }else if (tokens[index + 1].tokenType == EQUAL){
                Token name = tokens[index];
                index += 2;
                if (tokens[index].tokenType == ENDOFFILE){
                    Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected variable assignment");
                    return new Expression(EXPR_ERROR);
                }
                std::vector<Expression*> expressions;
                while (true){
                    expressions.push_back(ReadExpression(tokens,index));
                    if (expressions[expressions.size()-1]->type == EXPR_ERROR){
                        return new Expression(EXPR_ERROR);
                    }
                    if (tokens[index].tokenType == ENDOFFILE){
                        Error::SyntaxError(tokens[index-1].line,tokens[index-1].col,"expected semicolon");
                        return new Expression(EXPR_ERROR);
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
            }else{
                //exact copy of code in literal section
                TokenType type = tokens[index + 1].tokenType;
                std::vector<TokenType> operators = {PLUS,MINUS,SLASH,STAR,
                EQUAL_EQUAL,GREATER_EQUAL,LESS_EQUAL,LESS,GREATER};
                bool isOp = false;
                for (int i = 0; i < operators.size(); i ++){
                    if (operators[i] == type){
                        isOp = true;
                        break;
                    }
                }
                if (isOp){
                    std::vector<Expression*> exprs = {new ExprVariable(tokens[index])};
                    index ++;
                    Expression* operation = new Expression({tokens[index]});
                    operation->type = EXPR_PLACEHOLDER_OPERATOR;
                    exprs.push_back(operation);
                    index ++;
                    Expression* otherSide = ReadExpression(tokens,index);
                    if (otherSide->type == EXPR_ERROR){
                        return new Expression(EXPR_ERROR);
                    }
                    if (otherSide->type == EXPR_LIST){
                        ExprList* li = dynamic_cast<ExprList*>(otherSide);
                        for (int i = 0; i < li->exprs.size(); i ++){
                            exprs.push_back(li->exprs[i]);
                        }
                    }else{
                        exprs.push_back(otherSide);
                    }
                    return new ExprList(exprs);
                }
                // return new ExprVariable(tokens[index++]);
            }
        }
        Error::SyntaxError(tokens[index].line,tokens[index].col,"reached unparsable token");
        return new Expression(EXPR_ERROR);
    }
}