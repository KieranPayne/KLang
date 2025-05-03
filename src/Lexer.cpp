#include "Lexer.hpp"

namespace KLang{
    std::vector<Token> Lexer::Tokenize(std::string text){
        std::vector<Token> tokens;
        std::string currentToken = "";
        int line = 0;
        std::string splitChars = " ,.;+-/*()[]{}\n=<>\"\'";
        for (int i = 0; i < text.size(); i ++){
            if (text[i] == '\n'){
                ++line;
            }
            bool isSplit = false;
            for (int j = 0; j < splitChars.size(); j ++){
                if (text[i] == splitChars[j]){
                    AddToken(tokens,currentToken,line);
                    currentToken = text[i];
                    AddToken(tokens,currentToken,line);
                    currentToken = "";
                    isSplit = true;
                    break;
                }
            }
            if (isSplit){
                continue;
            }
            if (i >= text.size()){
                break;
            }
            currentToken += text[i];
        }
        if (currentToken.size() > 0){
            AddToken(tokens,currentToken,line);
        }
        return tokens;
    }
    void Lexer::AddToken(std::vector<Token>& tokens, std::string str, int line){
        bool isWhiteSpace = true;
        for (int i = 0; i < str.size(); i ++){
            if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'){
                isWhiteSpace = false;
                break;
            }
        }
        if (isWhiteSpace){
            return;
        }
        Token t(TokenType::TEST,str,line);
        tokens.push_back(t);
    }
};