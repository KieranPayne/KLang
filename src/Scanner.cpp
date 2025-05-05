#include "Scanner.hpp"
#include "Error.hpp"
#include <iostream>

namespace KLang
{
    std::vector<Token> Scanner::Scan(std::string text)
    {
        std::vector<Token> tokens;
        int line = 0;
        int startIndex = 0;
        int numToMatch = 36;
        std::string tokensToMatch[] = {"&&", "||", "class", "else", "false", "fn", "for", "if", "null", "return",
                                       "this", "true", "while", "!=", "!", "==", "=", ">=", ">", "<=", "<",
                                       "(", ")", "{", "}", "[", "]", ",", ".", "-", "+", "*", "/",";","break","continue"};
        TokenType tokenTypes[] = {AND, OR, CLASS, ELSE, FALSE, FN, FOR, IF, NULLVAL, RETURN, THIS, TRUE, WHILE, BANG_EQUAL, BANG, EQUAL_EQUAL, EQUAL,
                                  GREATER_EQUAL, GREATER, LESS_EQUAL, LESS, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_SQUARE, RIGHT_SQUARE, COMMA, DOT,
                                   MINUS, PLUS, STAR, SLASH, SEMICOLON,BREAK,CONTINUE};
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
                startIndex = i;
                continue;
            }
            if (stringFound(text, "//", i))
            {
                while (i < text.size() && text[i] != '\n')
                {
                    i++;
                }
                line++;
                startIndex = i;
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
                    Error::SyntaxError(line,i-startIndex-1,"missing closing quote");
                }
                str = DeEscape(str);
                tokens.push_back(Token(STRING,str,line,i - startIndex));
                continue;
            }
            bool tokenFound = false;
            for (int j = 0; j < numToMatch; j++)
            {
                if (stringFound(text, tokensToMatch[j], i))
                {
                    tokens.push_back(Token(tokenTypes[j], tokensToMatch[j], line,i-startIndex));
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
                                    Error::SyntaxError(line,i-startIndex, "failed to build number");
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
                        tokens.push_back(Token(INTEGER, num, line, i-startIndex));
                    }
                    else
                    {
                        tokens.push_back(Token(REAL, num, line, i-startIndex));
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
                        Error::SyntaxError(line,i-startIndex,str);
                        i ++;
                    }
                    i--;
                    tokens.push_back(Token(IDENTIFIER, val, line,i-startIndex));
                }
            }
        }
        tokens.push_back(Token(ENDOFFILE, "", line,0));

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
    std::string Scanner::DeEscape(std::string str){
        std::string result = "";
        for (int i = 0; i < str.size(); i ++){
            if (str[i] == '\\' && i < str.size() - 1){
                i ++;
                switch (str[i]){
                    case '\\':
                    result += '\\';
                    break;
                    case '\'':
                    result += '\'';
                    break;
                    case '\"':
                    result += '\"';
                    break;
                    case 'n':
                    result += '\n';
                    break;
                    case 'r':
                    result += '\r';
                    break;
                    case 't':
                    result += '\t';
                    break;
                    case 'b':
                    result += '\b';
                    break;
                    case 'f':
                    result += '\f';
                    break;
                    case '0':
                    result += '\0';
                    break;
                    case 'v':
                    result += '\v';
                    break;
                    case 'a':
                    result += '\a';
                    break;
                    default:
                    result += str[i];
                    break;
                }
            }else{
                result += str[i];
            }
        }
        return result;
    }
    
};