#pragma once
#include <string>
namespace KLang{
    enum TokenType{
                // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        LEFT_SQUARE,RIGHT_SQUARE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
        // One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals.
        IDENTIFIER, STRING, INTEGER, REAL,

        // Keywords.
        AND, CLASS, ELSE, FALSE, FN, FOR, IF, NULLVAL, OR,
        RETURN, THIS, TRUE, VAR, WHILE,BREAK,CONTINUE,

        ENDOFFILE
    };
    class Token{
        public:
        TokenType tokenType;
        std::string lexeme;
        int line;
        int col;
        
        void Print();
        Token(TokenType tokenType, std::string lexeme, int line, int col);
        
    };
    
}


