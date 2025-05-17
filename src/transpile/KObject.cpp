#include "KObject.hpp"
#include <vector>
namespace KLang{
    namespace KLangCompiled{
        KObject::KObject(){
            type = KOBJECT_NONE;
        }
        std::shared_ptr<KObject> KObject::UnaryOp(OperatorType op){
            return std::shared_ptr<KObject>(new KObject());
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
        std::shared_ptr<KObject> KObjReal::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            double val = std::dynamic_pointer_cast<KObjReal>(other)->value;
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
                return std::shared_ptr<KObject>(new KObjReal(value + val));
            }else if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjReal(value - val));
            }else if (op == OPERATOR_DIVIDE){
                return std::shared_ptr<KObject>(new KObjReal(value / val));
            }else if (op == OPERATOR_MULTIPLY){
                return std::shared_ptr<KObject>(new KObjInteger(value * val));
            }
        }
        std::shared_ptr<KObject> KObjString::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            std::string val = std::dynamic_pointer_cast<KObjString>(other)->value;
            if (op == OPERATOR_EQUAL){
                return std::shared_ptr<KObject>(new KObjBool(val == value));
            }else if (op == OPERATOR_NOTEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(val != value));
            }else if (op == OPERATOR_GREATER){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_GREATEREQUAL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_LESS){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_LESSEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_PLUS){
                return std::shared_ptr<KObject>(new KObjString(value + val));
            }else if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjNull());
            }else if (op == OPERATOR_DIVIDE){
                return std::shared_ptr<KObject>(new KObjNull());
            }else if (op == OPERATOR_MULTIPLY){
                return std::shared_ptr<KObject>(new KObjNull());
            }
        }
        std::shared_ptr<KObject> KObjBool::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            bool val = std::dynamic_pointer_cast<KObjBool>(other)->value;
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
                return std::shared_ptr<KObject>(new KObjBool(value <= val));
            }else if (op == OPERATOR_PLUS){
                return std::shared_ptr<KObject>(new KObjInteger(value + val));
            }else if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjInteger(value - val));
            }else if (op == OPERATOR_DIVIDE){
                return std::shared_ptr<KObject>(new KObjInteger(value / val));
            }else if (op == OPERATOR_MULTIPLY){
                return std::shared_ptr<KObject>(new KObjInteger(value * val));
            }
        }
        std::shared_ptr<KObject> KObjNull::OperationSameType(std::shared_ptr<KObject> other, OperatorType op){
            if (op == OPERATOR_EQUAL){
                return std::shared_ptr<KObject>(new KObjBool(true));
            }else if (op == OPERATOR_NOTEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_GREATER){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_GREATEREQUAL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_LESS){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (op == OPERATOR_LESSEQUAL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else{
                return std::shared_ptr<KObject>(new KObjNull());
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
        std::shared_ptr<KObject> KObjReal::Cast(KObjectType newType){
            if (newType == KOBJECT_INTEGER){
                return std::shared_ptr<KObject>(new KObjInteger((int)value));
            }else if (newType == KOBJECT_REAL){
                return std::shared_ptr<KObject>(new KObjReal(value));
            }else if (newType == KOBJECT_STRING){
                return std::shared_ptr<KObject>(new KObjString(std::to_string(value)));
            }else if (newType == KOBJECT_BOOL){
                return std::shared_ptr<KObject>(new KObjBool((value != 0)));
            }else if (newType == KOBJECT_NULL){
                return std::shared_ptr<KObject>(new KObjNull());
            }
        }
        std::shared_ptr<KObject> KObjString::Cast(KObjectType newType){
            if (newType == KOBJECT_INTEGER){
                try{
                    return std::shared_ptr<KObject>(new KObjInteger(std::stoi(value)));
                }catch(int i){
                    return std::shared_ptr<KObject>(new KObjNull());
                }
            }else if (newType == KOBJECT_REAL){
                try{
                    return std::shared_ptr<KObject>(new KObjInteger(std::stod(value)));
                }catch(int i){
                    return std::shared_ptr<KObject>(new KObjNull());
                }
            }else if (newType == KOBJECT_STRING){
                return std::shared_ptr<KObject>(new KObjString(value));
            }else if (newType == KOBJECT_BOOL){
                return std::shared_ptr<KObject>(new KObjBool((value == "true") ? true : false));
            }else if (newType == KOBJECT_NULL){
                return std::shared_ptr<KObject>(new KObjNull());
            }
        }
        std::shared_ptr<KObject> KObjBool::Cast(KObjectType newType){
            if (newType == KOBJECT_INTEGER){
                return std::shared_ptr<KObject>(new KObjInteger(value));
            }else if (newType == KOBJECT_REAL){
                return std::shared_ptr<KObject>(new KObjReal(value));
            }else if (newType == KOBJECT_STRING){
                return std::shared_ptr<KObject>(new KObjString((value) ? "true" : "false"));
            }else if (newType == KOBJECT_BOOL){
                return std::shared_ptr<KObject>(new KObjBool(value));
            }else if (newType == KOBJECT_NULL){
                return std::shared_ptr<KObject>(new KObjNull());
            }
        }
        std::shared_ptr<KObject> KObjNull::Cast(KObjectType newType){
            if (newType == KOBJECT_INTEGER){
                return std::shared_ptr<KObject>(new KObjInteger(0));
            }else if (newType == KOBJECT_REAL){
                return std::shared_ptr<KObject>(new KObjReal(0));
            }else if (newType == KOBJECT_STRING){
                return std::shared_ptr<KObject>(new KObjString("null"));
            }else if (newType == KOBJECT_BOOL){
                return std::shared_ptr<KObject>(new KObjBool(false));
            }else if (newType == KOBJECT_NULL){
                return std::shared_ptr<KObject>(new KObjNull());
            }
        }
        std::shared_ptr<KObject> KObjInteger::UnaryOp(OperatorType op){
            if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjInteger(-value));
            }else if (op == OPERATOR_NEGATE){
                return std::shared_ptr<KObject>(new KObjInteger((value == 0) ? 1 : 0));
            }
        }
        std::shared_ptr<KObject> KObjReal::UnaryOp(OperatorType op){
            if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjReal(-value));
            }else if (op == OPERATOR_NEGATE){
                return std::shared_ptr<KObject>(new KObjInteger((value == 0) ? 1 : 0));
            }
        }
        std::shared_ptr<KObject> KObjBool::UnaryOp(OperatorType op){
            if (op == OPERATOR_MINUS){
                return std::shared_ptr<KObject>(new KObjInteger((value) ? -1 : 0));
            }else if (op == OPERATOR_NEGATE){
                return std::shared_ptr<KObject>(new KObjBool(!value));
            }
        }
        std::shared_ptr<KObject> KObjString::UnaryOp(OperatorType op){
            return std::shared_ptr<KObject>(new KObjNull());
        }
        std::shared_ptr<KObject> KObjNull::UnaryOp(OperatorType op){
            return std::shared_ptr<KObject>(new KObjNull());
        }
        std::shared_ptr<KObject> KObjFromLiteral(int value){
            return std::shared_ptr<KObject>(new KObjInteger(value));
        }      
        std::shared_ptr<KObject> KObjFromLiteral(double value){
            return std::shared_ptr<KObject>(new KObjReal(value));
        } 
        std::shared_ptr<KObject> KObjFromLiteral(std::string value){
            return std::shared_ptr<KObject>(new KObjString(value));
        } 
        std::shared_ptr<KObject> KObjFromLiteral(bool value){
            return std::shared_ptr<KObject>(new KObjBool(value));
        }



    }
}