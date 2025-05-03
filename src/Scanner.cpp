#include "Scanner.hpp"
#include <iostream>

namespace KLang
{
    std::vector<Token> Scanner::Scan(std::string text)
    {
        std::vector<Token> tokens;
        int line = 0;
        int numToMatch = 37;

        std::string tokensToMatch[] = {"&&", "class", "else", "false", "fn", "for", "if", "null", "return",
                                       "this", "true", "var", "while", "!=", "!", "==", "=", ">=", ">", "<=", "<",
                                       "(", ")", "{", "}", "[", "]", ",", ".", "-=", "-", "+=", "+", "*=", "*", "/=", "/"};
        TokenType tokenTypes[] = {AND, CLASS, ELSE, FALSE, FN, FOR, IF, NULLVAL, RETURN, THIS, TRUE, VAR, WHILE, BANG_EQUAL, BANG, EQUAL_EQUAL, EQUAL,
                                  GREATER_EQUAL, GREATER, LESS_EQUAL, LESS, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_SQUARE, RIGHT_SQUARE, COMMA, DOT,
                                  MINUS_EQUAL, MINUS, PLUS_EQUAL, PLUS, STAR_EQUAL, STAR, SLASH_EQUAL, SLASH};
        std::string validVariableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] == ' ' || text[i] == '\t')
            {
                continue;
            }
            if (text[i] == '\n')
            {
                line++;
                continue;
            }
            if (stringFound(text, "//", i))
            {
                while (i < text.size() && text[i] != '\n')
                {
                    i++;
                }
                line++;
                continue;
            }
            if (text[i] == '\"'){
                i ++;
                bool foundClose = false;
                std::string str = "";
                while (i < text.size()){
                    if (text[i] == '\"'){
                        foundClose = true;
                        break;
                    }
                    if (text[i] == '\n'){
                        break;
                    }
                    str += text[i];
                    i ++;
                }
                if (!foundClose){
                    SyntaxError(line,"missing closing quote");
                    return {};
                }
                tokens.push_back(Token(STRING,str,line));
                continue;
            }
            bool tokenFound = false;
            for (int j = 0; j < numToMatch; j++)
            {
                if (stringFound(text, tokensToMatch[j], i))
                {
                    tokens.push_back(Token(tokenTypes[j], tokensToMatch[j], line));
                    tokenFound = true;
                    i += tokensToMatch[j].size() - 1;
                    break;
                }
            }
            if (!tokenFound)
            {
                if (isdigit(text[i]))
                {
                    bool isInt = true;
                    std::string num = "";
                    while (i < text.size())
                    {

                        if (isdigit(text[i]))
                        {
                            num += text[i];
                        }
                        else
                        {
                            if (text[i] == '.')
                            {
                                if (isInt)
                                {
                                    isInt = false;
                                    num += text[i];
                                }
                                else
                                {
                                    SyntaxError(line, "failed to build number");
                                return {};
                                }
                            }
                            else
                            {
                                i--;
                                break;
                            }
                        }
                        i ++;

                    }
                    if (isInt)
                    {
                        tokens.push_back(Token(INTEGER, num, line));
                    }
                    else
                    {
                        tokens.push_back(Token(REAL, num, line));
                    }
                }
                else
                {
                    std::string val = "";
                    while (i < text.size())
                    {
                        bool valid = false;
                        for (int j = 0; j < validVariableChars.size(); j++)
                        {
                            if (validVariableChars[j] == text[i] || isdigit(text[i]))
                            {
                                valid = true;
                                break;
                            }
                        }
                        if (!valid)
                        {
                            break;
                        }
                        val += text[i];
                        i ++;
                    }
                    if (val.size() == 0){
                        std::string str = "unexpected char found:";
                        str += text[i];
                        SyntaxError(line,str);
                        return {};
                    }
                    i--;
                    tokens.push_back(Token(IDENTIFIER, val, line));
                }
            }
        }
        tokens.push_back(Token(ENDOFFILE, "", line));

        return tokens;
    }
    bool Scanner::stringFound(std::string text, std::string str, int startIndex)
    {
        if (startIndex + str.size() > text.size())
        {
            return false;
        }
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] != text[startIndex + i])
            {
                return false;
            }
        }
        return true;
    }
    void Scanner::SyntaxError(int line, std::string message)
    {
        std::cout << "SYNTAX ERROR\nLINE:" << std::to_string(line) << " MSG:" << message << std::endl;
    }
};