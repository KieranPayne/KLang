#pragma once
#include "PCH.hpp"
class Token{
public:
enum TokenType{
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    CHAR_LITERAL,
    STR_LITERAL,
    OP,
    ASSIGN,
    SEMICOLON,
    ERROR,
};
TokenType type;
std::string lexeme;
int pos;
Token(TokenType type, std::string lexeme, int pos);
void Print();
};

class Lexer{
public:
Lexer();
std::vector<Token> Tokenize(std::string str);
private:
void ReadNextToken();
std::vector<Token> tokens;
std::string str;
int pos;
};
bool StrMatches(std::string& src, std::string& test, int pos);