#pragma once
#include <string>
namespace KLang{
    enum TokenType{
                // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        LEFT_SQUARE,RIGHT_SQUARE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
        PLUS_EQUAL,MINUS_EQUAL,STAR_EQUAL,SLASH_EQUAL,
        // One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals.
        IDENTIFIER, STRING, INTEGER, REAL,

        // Keywords.
        AND, CLASS, ELSE, FALSE, FN, FOR, IF, NULLVAL, OR,
        RETURN, THIS, TRUE, VAR, WHILE,

        ENDOFFILE
    };
    class Token{
        public:
        TokenType tokenType;
        std::string lexeme;
        int line;
        
        void Print();
        Token(TokenType tokenType, std::string lexeme, int line);
        
    };
    
}


