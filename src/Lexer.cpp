#include "Lexer.hpp"

std::vector<std::string> KEYWORDS = {
    "auto","extrn","case","if","while","switch","return"
};

std::vector<std::string> OPS = {
    "|","&","==","!=","<","<=",">",">=","<<",">>",
    "-","+","%","*","/","!","++","--",","
};


Token::Token(TokenType type, std::string lexeme, int pos){
    this->type = type;
    this->lexeme = lexeme;
    this->pos = pos;
}

void Token::Print(){
    std::cout << "[ " << lexeme << " " << type << "]"; 
}

Lexer::Lexer(){
    pos = 0;
    str = "";
    tokens = {};
}

std::vector<Token> Lexer::Tokenize(std::string str){
    this->str = str;
    pos = 0;
    tokens = {};
    while (pos < str.size()){
        //check for comment
        if (pos < str.size() - 1){
            if (str[pos] == '/' && str[pos + 1] == '*'){
                pos += 2;
                while (true){
                    if (pos >= str.size() - 1){
                        tokens.push_back(Token(Token::ERROR,"Expected */",pos));
                        break;
                    }
                    if (str[pos] == '*' && str[pos + 1] == '/'){
                        pos += 2;
                        break;
                    }
                    pos ++;
                }
                continue;
            }
        }
        //check for new line or space
        if (str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n'){
            pos ++;
            continue;
        }
        ReadNextToken();
    }
    for (auto& t : tokens){
        t.Print();
    }
    return tokens;
}

void Lexer::ReadNextToken(){
    //look for keyword
    for (auto& keyword : KEYWORDS){
        if (StrMatches(str,keyword,pos)){
            tokens.push_back(Token(Token::KEYWORD,keyword,pos));
            pos += keyword.size();
            return;
        }
    }
    //look for bin op
    for (auto& op : OPS){
        if (StrMatches(str,op,pos)){
            tokens.push_back(Token(Token::OP,op,pos));
            pos += op.size();
            return;
        }
    }
    //look for assignment
    if (str[pos] == '='){
        tokens.push_back(Token(Token::ASSIGN,std::string(1,str[pos]),pos));
        pos ++;
        return;
    }
    //look for semicolon
    if (str[pos] == ';'){
        tokens.push_back(Token(Token::SEMICOLON,std::string(1,str[pos]),pos));
        pos ++;
        return;
    }
    if (str[pos] == '\"'){
        std::string val = "";
        pos ++;
        while (pos < str.size() && str[pos] != '\"'){
            val += str[pos];
            pos ++;
        }
        if (pos == str.size()){
            tokens.push_back(Token(Token::ERROR,"Expected closing quote",pos));
            return;
        }
        //skip closing quote
        pos ++;
        tokens.push_back(Token(Token::STR_LITERAL,val,pos - val.size() - 2));
        return;
    }
    if (str[pos] == '\''){
        std::string val = "";
        pos ++;
        while (pos < str.size() && str[pos] != '\''){
            val += str[pos];
            pos ++;
        }
        if (pos == str.size()){
            tokens.push_back(Token(Token::ERROR,"Expected closing quote",pos));
            return;
        }
        if (val.size() == 0){
            tokens.push_back(Token(Token::ERROR,"Expected character in literal",pos));
            pos ++;
            return;
        }
        //skip closing quote
        pos ++;
        tokens.push_back(Token(Token::CHAR_LITERAL,val,pos - val.size() - 2));
        return;
    }
    if (isdigit(str[pos])){
        std::string num(1,str[pos]);
        pos ++;
        while (pos < str.size() && isdigit(str[pos])){
            num += str[pos];
            pos ++;
        }
        tokens.push_back(Token(Token::NUMBER,num,pos-num.size()));
        return;
    }
    if (isalpha(str[pos])){
        std::string ident(1,str[pos]);
        pos ++;
        while (pos < str.size() && isalnum(str[pos])){
            ident += str[pos];
            pos ++;
        }
        tokens.push_back(Token(Token::IDENTIFIER,ident,pos - ident.size()));
        return;
    }
    tokens.push_back(Token(Token::KEYWORD,std::string(1,str[pos]),pos));
    pos ++;
}

bool StrMatches(std::string& src, std::string& test, int pos){
    if (pos + test.size() > src.size()){
        return false;
    }
    for (int i = 0; i < test.size(); i ++){
        if (test[i] != src[pos + i]){
            return false;
        }
    }
    return true;
}