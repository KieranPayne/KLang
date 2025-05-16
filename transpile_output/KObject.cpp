#include "KObject.hpp"
#include <vector>
namespace KLang{
    namespace KLangCompiled{
        KObject::KObject(){
            type = KOBJECT_NONE;
        }
        KObject::~KObject(){}
        std::shared_ptr<KObject> KObject::Operation(std::shared_ptr<KObject> other, OperatorType op){
            KObjectType precedence[] = {
                KOBJECT_NULL,
                KOBJECT_STRING,
                KOBJECT_REAL,
                KOBJECT_INTEGER,
                KOBJECT_BOOL
            };
            int precedenceSize = 5;
            for (int i = 0; i < precedenceSize; i ++){
                if (type == precedence[i]){
                    std::shared_ptr<KObject> casted = other->Cast(precedence[i]);
                    return OperationSameType(casted,op);
                }else if (other->type == precedence[i]){
                    std::shared_ptr<KObject> casted = Cast(precedence[i]);
                    return other->OperationSameType(casted,op);
                }
            }
        }
        std::shared_ptr<KObject> KObject::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            return other;
        }
        std::shared_ptr<KObject> KObject::Cast(KObjectType newType){
            return std::make_shared<KObject>();
        }

    }
}
