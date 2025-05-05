#pragma once
#include <string>   
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
    class ObjNull;
    class Object{
        public:
        ObjectType type;
        Object();
        ~Object(){}
        virtual void Print();
        virtual Object* Cast(ObjectType type){}
    };
    class ObjString : public Object{
        public:
        std::string value;
        ObjString(std::string value);
        ~ObjString(){}
        void Print();
        Object* Cast(ObjectType type);
    };
    class ObjBool : public Object{
        public:
        bool value;
        ObjBool(bool value);
        ~ObjBool(){}
        void Print();
        Object* Cast(ObjectType type);

    };
    class ObjInteger : public Object{
        public:
        int value;
        ObjInteger(int value);
        ~ObjInteger(){}
        void Print();
        Object* Cast(ObjectType type);

    };
    class ObjReal : public Object{
        public:
        float value;
        ObjReal(float value);
        ~ObjReal(){}
        void Print();
        Object* Cast(ObjectType type);

    };
    class ObjNull : public Object{
        public:
        ObjNull();
        ~ObjNull(){}
        void Print();
        Object* Cast(ObjectType type);
    };
}