#pragma once
#include <memory>
#include "Token.hpp"
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
        class KObject{
            public:
            KObjectType type;
            KObject();
            ~KObject();
            std::shared_ptr<KObject> Operation(std::shared_ptr<KObject> other, TokenType op);
            virtual std::shared_ptr<KObject> OperationSameType(std::shared_ptr<KObject> other, TokenType op);
            virtual std::shared_ptr<KObject> Cast(KObjectType newType);
        };
    }
}
