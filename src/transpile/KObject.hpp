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
            OPERATOR_GREATEREQUAL
        };
        class KObject : public std::enable_shared_from_this<KObject>{
            public:
            KObjectType type;
            KObject();
            ~KObject();
            std::shared_ptr<KObject> Operation(std::shared_ptr<KObject> other, OperatorType op);
            virtual std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            virtual std::shared_ptr<KObject> Cast(KObjectType newType);
        };
        class KObjInteger : public KObject{
            public:
            int value;
            KObjInteger(int value);
            std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            std::shared_ptr<KObject> Cast(KObjectType newType);
        };
        class KObjReal : public KObject{
            public:
            double value;
            KObjReal(double value);
            // std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            // std::shared_ptr<KObject> Cast(KObjectType newType);
        };
        class KObjString : public KObject{
            public:
            std::string value;
            KObjString(std::string value);
            // std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            // std::shared_ptr<KObject> Cast(KObjectType newType);
        };
        class KObjBool : public KObject{
            public:
            bool value;
            KObjBool(bool value);
            // std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            // std::shared_ptr<KObject> Cast(KObjectType newType);
        };
        class KObjNull : public KObject{
            public:
            KObjNull();
            // std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            // std::shared_ptr<KObject> Cast(KObjectType newType);
        };
    }
}
