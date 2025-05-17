#include "KObject.hpp"
#include <vector>
namespace KLang{
    namespace KLangCompiled{
        KObject::KObject(){
            type = KOBJECT_NONE;
        }
        KObject::~KObject(){}
        std::shared_ptr<KObject> KObject::Operation(std::shared_ptr<KObject> other, OperatorType op){
            if (op == OPERATOR_EQUAL || op == OPERATOR_NOTEQUAL){
                if (other->type != type){
                    return std::shared_ptr<KObject>(new KObjBool(false));
                }else{
                    return OperationSameType(other,op);
                }
            }else if (op == OPERATOR_LESSEQUAL || op == OPERATOR_LESS || op == OPERATOR_GREATEREQUAL || op == OPERATOR_GREATER){
                KObjectType precedence[] = {
                    KOBJECT_NULL,
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
            }else{
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
            
        }
        std::shared_ptr<KObject> KObject::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            return other;
        }
        std::shared_ptr<KObject> KObject::Cast(KObjectType newType){
            return std::make_shared<KObject>();
        }

        KObjInteger::KObjInteger(int value){
            this->value = value;
            type = KOBJECT_INTEGER;
        }
        KObjReal::KObjReal(double value){
            this->value = value;
            type = KOBJECT_REAL;
        }
        KObjString::KObjString(std::string value){
            this->value = value;
            type = KOBJECT_STRING;
        }
        KObjBool::KObjBool(bool value){
            this->value = value;
            type = KOBJECT_BOOL;
        }
        KObjNull::KObjNull(){
            type = KOBJECT_NULL;
        }
        std::shared_ptr<KObject> KObjInteger::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            int val = std::dynamic_pointer_cast<KObjInteger>(other)->value;
            if (op == OPERATOR_EQUAL){
                return std::shared_ptr<KObject>(new KObjBool(val == value));
            }else if (op == OPERATOR_NOTEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(val != value));
            }else if (op == OPERATOR_GREATER){
                return std::shared_ptr<KObject>(new KObjBool(value > val));
            }else if (op == OPERATOR_GREATEREQUAL){
                return std::shared_ptr<KObject>(new KObjBool(value >= val));
            }else if (op == OPERATOR_LESS){
                return std::shared_ptr<KObject>(new KObjBool(value < val));
            }else if (op == OPERATOR_LESSEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(value < val));
            }else if (op == OPERATOR_PLUS){
                return std::shared_ptr<KObject>(new KObjInteger(value + val));
            }else if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjInteger(value - val));
            }else if (op == OPERATOR_DIVIDE){
                double result = value / val;
                if (result != (int)result){
                    return std::shared_ptr<KObject>(new KObjReal(result));
                }
                return std::shared_ptr<KObject>(new KObjInteger(result));
            }else if (op == OPERATOR_MULTIPLY){
                return std::shared_ptr<KObject>(new KObjInteger(value * val));
            }
        }
        std::shared_ptr<KObject> KObjInteger::Cast(KObjectType newType){
            if (newType == KOBJECT_INTEGER){
                return std::shared_ptr<KObject>(new KObjInteger(value));
            }else if (newType == KOBJECT_REAL){
                return std::shared_ptr<KObject>(new KObjReal((double)value));
            }else if (newType == KOBJECT_STRING){
                return std::shared_ptr<KObject>(new KObjString(std::to_string(value)));
            }else if (newType == KOBJECT_BOOL){
                return std::shared_ptr<KObject>(new KObjBool((value != 0)));
            }else if (newType == KOBJECT_NULL){
                return std::shared_ptr<KObject>(new KObjNull());

            }
        }
        


    }
}
