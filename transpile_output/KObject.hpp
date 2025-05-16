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
            OPERATOR_DIVIDE
        };
        class KObject{
            public:
            KObjectType type;
            KObject();
            ~KObject();
            std::shared_ptr<KObject> Operation(std::shared_ptr<KObject> other, OperatorType op);
            std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, OperatorType op);
            std::shared_ptr<KObject> Cast(KObjectType newType);
        };
    }
}
