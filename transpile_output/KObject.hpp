#pragma once
#include <memory>
namespace KLang{
    namespace KLangCompiled{
        enum KObjectType{
            KOBJECT_NONE,
            KOBJECT_NULL,
            KOBJECT_STRING,
            KOBJECT_REAL,
            KOBJECT_INTEGER,
            KOBJECT_BOOL,
        };
        enum OperatorType{
            OPERATOR_PLUS,
            OPERATOR_MINUS,
            OPERATOR_MULTIPLY,
            OPERATOR_DIVIDE,
            OPERATOR_EQUAL,
            OPERATOR_NOTEQUAL,
            OPERATOR_LESS,
            OPERATOR_LESSEQUAL,
            OPERATOR_GREATER,
            OPERATOR_GREATEREQUAL,
            OPERATOR_NEGATE
        };
        class KObject{
            public:
            KObjectType type;
            union
            {
                std::string* strVal;
                double doubleVal;
                int intVal;
            };
            //blank constructor initialises as null by default
            KObject();
            KObject(int value);
            KObject(double value);
            KObject(std::string value);
            KObject(bool value);
            ~KObject();
            // KObject Operation(KObject& other, OperatorType op);
            KObject Equality(KObject& other, bool equals);
            KObject Comparison(KObject& other, OperatorType op);
            KObject Arithmetic(KObject& other, OperatorType op);
            KObject Cast(KObjectType newType);
            KObject UnaryOp(OperatorType op);
        };
    }
}
