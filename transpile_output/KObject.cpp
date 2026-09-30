#include "KObject.hpp"
#include <vector>
#define ISINT type == KOBJECT_INTEGER
#define ISREAL type == KOBJECT_REAL
#define ISSTRING type == KOBJECT_STRING
#define ISBOOL type == KOBJECT_BOOL
#define ISNULL type == KOBJECT_NULL

namespace KLang{
    namespace KLangCompiled{
        KObject::KObject(){
            type = KOBJECT_NULL;
        }
        KObject KObject::UnaryOp(OperatorType op){
            // return std::shared_ptr<KObject>(new KObject());
            if (op == OPERATOR_MINUS){
                if (ISINT){
                    return KObject(-intVal);
                }else if (type == KOBJECT_REAL){
                    return KObject(-doubleVal);
                }
                return KObject();
            }else if (op == OPERATOR_NEGATE){
                if (ISBOOL || ISINT){
                    return KObject(!intVal);
                }else if (ISREAL){
                    return KObject(!doubleVal);
                }
                return KObject();
            }
            return KObject();
        }
        KObject::KObject(int value){
            type = KOBJECT_INTEGER;
            intVal = value;
        }
        KObject::KObject(double value){
            type = KOBJECT_REAL;
            doubleVal = value;
        }
        KObject::KObject(std::string value){
            type = KOBJECT_STRING;
            strVal = new std::string(value);
        }
        KObject::KObject(bool value){
            type = KOBJECT_BOOL;
            intVal = value;
        }

        KObject::~KObject(){
            if (type == KOBJECT_STRING){
                delete strVal;
            }
        }
        
        KObject KObject::Equality(KObject other, bool equals){
            KObject result;
            if (other.type == type){
                if (ISINT || ISBOOL){
                    result = KObject(intVal == other.intVal);
                }else if (ISREAL){
                    result = KObject(doubleVal == other.doubleVal);
                }else if (ISSTRING){
                    result = KObject(*strVal == *other.strVal);
                }else{
                    //null val should always return true
                    result = KObject(true);
                }
            }else if (other. ISINT && ISREAL){
                result = KObject(other.intVal == doubleVal);
            }else if (other. ISREAL && ISINT){
                result = KObject(other.doubleVal == intVal);
            }else{
                result = KObject(false);
            }
            if (!equals){
                result.intVal = !result.intVal;
            }
            return result;
        }
        KObject KObject::Comparison(KObject other, OperatorType op){
            bool greater;
            bool equal;
            if (ISINT && other. ISINT){
                greater = intVal > other.intVal;
                equal = intVal == other.intVal;
            }else if (ISREAL && other. ISINT){
                greater = doubleVal > other.intVal;
                equal = doubleVal == other.intVal;
            }else if (ISINT && other. ISREAL){
                greater = intVal > other.doubleVal;
                equal = intVal == other.doubleVal;
            }else{
                return KObject(false);
            }
            switch ((int)op){
                case (int)OPERATOR_GREATER:
                    return KObject(greater);
                case (int)OPERATOR_GREATEREQUAL:
                    return KObject(greater || equal);
                case (int)OPERATOR_LESS:
                    return KObject(!greater && !equal);
                case (int)OPERATOR_LESSEQUAL:
                    return KObject(!greater);
            }
        }
        KObject KObject::Arithmetic(KObject other, OperatorType op){
            if (ISSTRING){
                return KObject( *strVal + *other.Cast(KOBJECT_STRING).strVal);
            }
            if (other. ISREAL){
                double myVal;
                if (ISREAL){
                    myVal = doubleVal;
                }else if (ISINT || ISBOOL){
                    myVal = (double)intVal;
                }else{
                    return KObject();
                }
                switch ((int)op){
                    case (int)OPERATOR_PLUS:
                        return KObject(myVal + other.doubleVal);
                    case (int)OPERATOR_MINUS:
                        return KObject(myVal - other.doubleVal);
                    case (int)OPERATOR_DIVIDE:
                        return KObject(myVal / other.doubleVal);
                    case (int)OPERATOR_MULTIPLY:
                        return KObject(myVal * other.doubleVal);
                }
            }else if (other. ISINT || other. ISBOOL){
                if (ISINT || ISBOOL){
                    double result;
                    switch ((int)op)
                    {
                        case (int)OPERATOR_DIVIDE:
                            result = (double)intVal / (double)other.intVal;
                            if (result != (int)result){
                                return KObject(result);
                            }else{
                                return KObject((int)result);
                            }
                            break;
                        case (int)OPERATOR_MULTIPLY:
                            return KObject(intVal * other.intVal);
                        case (int)OPERATOR_PLUS:
                            return KObject(intVal + other.intVal);
                        case (int)OPERATOR_MINUS:
                            return KObject(intVal - other.intVal);
                    }
                }else{
                    if (type != KOBJECT_REAL){
                        return KObject();
                    }
                    double otherVal = (double)other.intVal;
                    switch ((int)op){
                        case (int)OPERATOR_PLUS:
                            return KObject(doubleVal + otherVal);
                        case (int)OPERATOR_MINUS:
                            return KObject(doubleVal - otherVal);
                        case (int)OPERATOR_DIVIDE:
                            return KObject(doubleVal / otherVal);
                        case (int)OPERATOR_MULTIPLY:
                            return KObject(doubleVal * otherVal);
                    }
                }
            }
            return KObject();
        }
        KObject KObject::Cast(KObjectType newType){
            switch ((int)newType){
                case (int)KOBJECT_STRING:
                {
                    switch ((int)type){
                        case (int)KOBJECT_INTEGER:
                            return KObject(std::to_string(intVal));
                        case (int)KOBJECT_REAL:
                            return KObject(std::to_string(doubleVal));
                        case (int)KOBJECT_BOOL:
                            return KObject(intVal ? "true" : "false");
                        case (int)KOBJECT_STRING:
                            return KObject(*strVal);
                        case (int)KOBJECT_NULL:
                            return KObject("null");
                    }
                }
                case (int)KOBJECT_INTEGER:
                {
                    switch ((int)type){
                        case (int)KOBJECT_INTEGER:
                            return KObject(intVal);
                        case (int)KOBJECT_BOOL:
                            return KObject(intVal);
                        case (int)KOBJECT_REAL:
                            return KObject((int)doubleVal);
                        case (int)KOBJECT_STRING:
                        {
                            try{
                                return KObject(std::stoi(*strVal));
                            }
                            catch (int i ){
                                return KObject();
                            }
                        }
                        case (int)KOBJECT_NULL:
                            return KObject();
                    }
                }
                case (int)KOBJECT_REAL:
                {
                    switch ((int)type){
                        case (int)KOBJECT_INTEGER:
                            return KObject((double)intVal);
                        case (int)KOBJECT_REAL:
                            return KObject(doubleVal);
                        case (int)KOBJECT_STRING:
                        {
                            try{
                                return KObject(std::stod(*strVal));
                            }catch (int i ){
                                return KObject();
                            }
                        }
                        case (int)KOBJECT_BOOL:
                            return KObject((double)intVal);
                        case (int)KOBJECT_NULL:
                            return KObject();
                    }
                }
                case (int)KOBJECT_BOOL:
                {
                    switch ((int)type){
                        case (int)KOBJECT_INTEGER:
                            return KObject(intVal != 0);
                        case(int)KOBJECT_REAL:
                            return KObject(doubleVal != 0);
                        case (int)KOBJECT_BOOL:
                            return KObject((bool)intVal);
                        case (int)KOBJECT_STRING:
                            return KObject(*strVal == "true");
                        case (int)KOBJECT_NULL:
                            return KObject(false);
                    }
                }
                case (int)KOBJECT_NULL:
                    return KObject();
            }
        }
        bool KObject::AsBool(){
            if (ISBOOL){
                return intVal;
            }
            return Cast(KOBJECT_BOOL).intVal;
        }
    }
}

#undef ISINT
#undef ISREAL
#undef ISSTRING
#undef ISBOOL
#undef ISNULL
