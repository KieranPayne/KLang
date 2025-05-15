#include "Parser.hpp"
#include <iostream>
namespace KLang{
    using namespace TreeNode;
    Parser::Parser(std::vector<Token> tokens){
        this->tokens = tokens;
        current = 0;
        panicMode = false;
        Node* expr = program();
        if (!panicMode){
            expr->Print();
        }
    }
    void Parser::SkipStatement(){
        while (Current().tokenType != ENDOFFILE){
            if (Current().tokenType == SEMICOLON){
                current ++;
                break;
            }
            switch (Advance().tokenType){
                case CLASS:
                case FN:
                case VAR:
                case FOR:
                case WHILE:
                case IF:
                case RETURN:
                case BREAK:
                
                return;
            }
        }
    }
    Node* Parser::program(){
        std::vector<Node*> stmts;
        while (Current().tokenType != ENDOFFILE){
            try{
                stmts.push_back(statement());
            }catch(Error e){
                SkipStatement();
            }
        }
        return new Program(stmts);
    }
    Node* Parser::statement(){
        if (Check(WHILE)){
            return whileStmt();
        }else if (Check(IF)){
            return ifStmt();
        }else if (Check(FOR)){
            return forStmt();
        }else if (Check(RETURN)){
            return returnStmt();
        }else if (Check(LEFT_BRACE)){
            return block();
        }else if (Check(FN)){
            return funcDec();
        }else if (Check(VAR)){
            return varDec();
        // }else if (Check(CLASS)){ //cba to do this rn
        //     return classDec();
        }else{
            return exprStmt();
        }
    }
    Node* Parser::whileStmt(){
        Consume(WHILE,"expect while");
        Node* condition = grouping();
        Node* block = statement();
        return new While(condition,block);
    }
    Node* Parser::ifStmt(){
        Consume(IF,"expect if");
        Node* condition = grouping();
        Node* trueBlock = statement();
        Node* falseBlock = nullptr;
        if (Check(ELSE)){
            Consume(ELSE,"");
            falseBlock = statement();
        }
        return new If(condition,trueBlock,falseBlock);
    }
    Node* Parser::exprStmt(){
        Node* expr = expression();
        Consume(SEMICOLON,"expect semicolon");
        return new ExprStmt(expr);
    }
    Node* Parser::returnStmt(){
        Consume(RETURN,"expect return");
        Node* expr = nullptr;
        if (!Check(SEMICOLON)){
            expr = expression();
        }
        Consume(SEMICOLON,"expect semicolon");
        return new ReturnStmt(expr);
    }
    Node* Parser::block(){
        Consume(LEFT_BRACE,"expect {");
        std::vector<Node*> statements = {};
        while (!Check(RIGHT_BRACE)){
            statements.push_back(statement());
            if (Check(ENDOFFILE)){
                ReportError(Error(Current(),"expect closing brace",true));
            }
        }
        Advance();
        return new Block(statements);
    }
    Node* Parser::forStmt(){
        Consume(FOR, "expect for");
        Consume(LEFT_PAREN, "expect left paren");
        Node* dec = statement();
        Node* condition = expression();
        Consume(SEMICOLON,"expect semicolon");
        Node* endOfLoop = expression();
        Consume(RIGHT_PAREN, "expect left paren");
        Node* loopBlock = statement();
        return new For(dec,condition,endOfLoop,loopBlock);
    }
    Node* Parser::varDec(){
        Consume(VAR,"expect var keyword");
        Token name = Advance();
        Node* expr = nullptr;
        if (Check(EQUAL)){
            Consume(EQUAL,"expect equal");
            expr = expression();
        }
        Consume(SEMICOLON,"expect semicolon"); 
        return new VarDec(name,expr);
    }
    Node* Parser::funcDec(){
        Consume(FN, "expect fn keyword");
        if (!Check(IDENTIFIER)){
            ReportError(Error(Current(),"expect function name",true));
        }
        Token name = Advance();
        std::vector<Token> args = {};
        Consume(LEFT_PAREN, "expect left paren");
        while (!Check(RIGHT_PAREN)){
            if (!Check(IDENTIFIER)){
                ReportError(Error(Current(),"expect right paren",true));
            }
            args.push_back(Advance());
            if (Check(COMMA)){
                Advance();
            }
        }
        Advance(); //skip right paren
        Node* codeBlock = block();
        return new FuncDec(name,args,codeBlock);
    }
    Node* Parser::expression(){
        return assignment();
    }
    Node* Parser::assignment(){
        Node* expr = equality();
        if (Check(EQUAL)){
            Token name = Previous();
            if (expr->type != NODE_VARIABLE){
                ReportError(Error(name,"expect variable name",true));
            }
            delete expr;
            Advance();
            expr = expression();
            // Consume(SEMICOLON,"expect semicolon");
            return new Assignment(name,expr);
        }
        return expr;
    }
    Node* Parser::equality(){
        Node* node = comparison();
        while (Match({BANG_EQUAL,EQUAL_EQUAL})){
            Token op = Advance();
            Node* right = comparison();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::comparison(){
        Node* node = term();
        while (Match({LESS,LESS_EQUAL,GREATER,GREATER_EQUAL})){
            Token op = Advance();
            Node* right = term();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::term(){
        Node* node = factor();
        while (Match({PLUS,MINUS})){
            Token op = Advance();
            Node* right = factor();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::factor(){
        Node* node = unary();
        while (Match({STAR,SLASH})){
            Token op = Advance();
            Node* right = unary();
            node = new Binary(node,right,op);
        }
        return node;
    }
    Node* Parser::unary(){
        if (Match({BANG,MINUS})){
            Token op = Advance();
            return new Unary(unary(),op);
        }else if (Check(LEFT_PAREN)){
            return grouping();
        }else{
            return primary();
        }
    }
    Node* Parser::grouping(){
        Consume(LEFT_PAREN,"expect left paren");
        Node* node = expression();
        Consume(RIGHT_PAREN,"expect right paren");
        return new Grouping(node);
    }
    Node* Parser::primary(){
        if (Check(IDENTIFIER)){
            current++;
            if (Check(LEFT_PAREN)){
                current--;
                return call();
            }
            current --;
            return new Variable(Advance());
        }
        return literal();
    }
    Node* Parser::literal(){
        if (Match({STRING,INTEGER,REAL,TRUE,FALSE,NULLVAL})){
            return new Literal(Advance());
        }else{
            if (Check(TOKEN_ERROR)){
                ReportError(Error(Current(),Current().lexeme,true));
            }
            ReportError(Error(Advance(),"expected literal",true));
        }
    }
    Node* Parser::call(){
        Token name = Advance();
        Consume(LEFT_PAREN,"expect (");
        std::vector<Node*> args = {};
        while (!Check(RIGHT_PAREN)){
            args.push_back(expression());
            if (Check(COMMA)){
                Advance();
            }
            if (Check(ENDOFFILE)){
                ReportError(Error(Current(),"expect )",true));
            }
        }
        Advance();
        return new Call(name,args);
    }

    //helper functions
    Token Parser::Previous(){
        return tokens[current - 1];
    }
    Token Parser::Current(){
        return tokens[current];
    }
    Token Parser::Advance(){
        current ++;
        Token t = Current();
        while (t.tokenType == TOKEN_ERROR){
            ReportError(Error(t,t.lexeme,false));
            tokens.erase(tokens.begin() + current);
            t = Current();
        }
        return Previous();
    }
    bool Parser::atEnd(){
        return Current().tokenType == EOF;
    }
    bool Parser::Check(TokenType type){
        
        return Current().tokenType == type;
    }
    bool Parser::Match(std::vector<TokenType> types){
        for (int i = 0; i < types.size(); i ++){
            if (Check(types[i])){
                return true;
            }
        }
        return false;
    }
    void Parser::Consume(TokenType type, std::string message){
        if (Check(type)){
            Advance();
        }else{
            ReportError(Error(Current(),message,true));
            //error handling goes here
        }
    }
    
    void Parser::ReportError(Error e){
        panicMode = true;
        if (e.token.tokenType == ENDOFFILE){
            std::cout << "error at end of file";
        }else{
            std::cout << "error at line: " << (e.token.line + 1) << " col: " << (e.token.col + 1);
        }

        std::cout << "\n" << e.message << "\n";
        if (e.sync){
            throw e;
        }
    }
    Error::Error(Token token, std::string message, bool sync){
        this->token= token;
        this->sync = sync;
        this->message = message;
    }
}