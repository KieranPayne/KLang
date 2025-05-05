#pragma once
#include <string>   
#include <vector>
#include "Token.hpp"
#include "Error.hpp"
namespace KLang{
    enum ObjectType{
        OBJ_STRING,
        OBJ_BOOL,
        OBJ_INTEGER,
        OBJ_REAL,
        OBJ_NULL,
        OBJ_NONE
    };
    extern const std::vector<ObjectType> precedence; 
    class ObjNull;
    class Object{
        public:
        ObjectType type;
        Object();
        ~Object(){}
        virtual Object* Operation(Object* other, TokenType op, bool convert);
        virtual Object* OperationSameType(Object* other, TokenType op, bool lhs);
        virtual void Print();
        virtual Object* Cast(ObjectType type){}
        bool variableVal;
    };
    class ObjString : public Object{
        public:
        std::string value;
        ObjString(std::string value);
        ~ObjString(){}
        void Print();
        Object* OperationSameType(Object* other, TokenType op, bool lhs);
        Object* Cast(ObjectType type);
    };
    class ObjBool : public Object{
        public:
        bool value;
        ObjBool(bool value);
        ~ObjBool(){}
        void Print();
        Object* OperationSameType(Object* other, TokenType op, bool lhs);
        Object* Cast(ObjectType type);

    };
    class ObjInteger : public Object{
        public:
        int value;
        ObjInteger(int value);
        ~ObjInteger(){}
        void Print();
        Object* OperationSameType(Object* other, TokenType op, bool lhs);
        Object* Cast(ObjectType type);

    };
    class ObjReal : public Object{
        public:
        double value;
        ObjReal(double value);
        ~ObjReal(){}
        void Print();
        Object* OperationSameType(Object* other, TokenType op, bool lhs);
        Object* Cast(ObjectType type);

    };
    class ObjNull : public Object{
        public:
        ObjNull();
        ~ObjNull(){}
        void Print();
        Object* OperationSameType(Object* other, TokenType op, bool lhs);
        Object* Cast(ObjectType type);
    };
}