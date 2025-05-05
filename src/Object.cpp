#include "Object.hpp"
#include "Token.hpp"
#include <iostream>
#include <vector>
namespace KLang{
    const std::vector<ObjectType> precedence = {OBJ_NULL,OBJ_STRING,OBJ_REAL,OBJ_INTEGER,OBJ_BOOL};

    Object::Object(){
        type = OBJ_NONE;
    }
    ObjString::ObjString(std::string value){
        this->value = value;
        type = OBJ_STRING;
    }
    ObjBool::ObjBool(bool value){
        this->value = value;
        type = OBJ_BOOL;
    }
    ObjInteger::ObjInteger(int value){
        this->value = value;
        type = OBJ_INTEGER;
    }
    ObjReal::ObjReal(double value){
        this->value = value;
        type = OBJ_REAL;
    }
    ObjNull::ObjNull(){
        type = OBJ_NULL;
    }
    void Object::Print(){
        std::cout << "NONE TYPE OBJECT";
    }
    void ObjString::Print(){
        std::cout << value;
    }
    void ObjBool::Print(){
        std::cout << (value) ? "true" : "false";
    }
    void ObjInteger::Print(){
        std::cout << std::to_string(value);
    }
    void ObjReal::Print(){
        std::cout << std::to_string(value);
    }
    void ObjNull::Print(){
        std::cout << "null";
    }



    //casting
    Object* ObjString::Cast(ObjectType type){
        if (type == OBJ_STRING){
            return new ObjString(value);
        }else if (type == OBJ_REAL){
            Object* result;
            try{
                float val = std::stod(value);
                result = new ObjReal(val);
            }catch (int x){
                result = new ObjNull();
            }
            return result;
        }else if (type == OBJ_INTEGER){
            Object* result;
            try{
                int val = std::stoi(value);
                result = new ObjInteger(val);
            }catch (int x){
                result = new ObjNull();
            }
            return result;
        }else if (type == OBJ_BOOL){
            Object* result;
            if (value == "true"){
                result = new ObjBool(true);
            }else{
                result = new ObjBool(false);
            }
            return result;
        }else{
            return new ObjNull();
        }
    }
    Object* ObjInteger::Cast(ObjectType type){
        if (type == OBJ_STRING){
            Object* result = new ObjString(std::to_string(value));
            return result;
        }else if (type == OBJ_INTEGER){
            return new ObjInteger(value);
        }else if (type == OBJ_REAL){
            Object* result = new ObjReal((double)value);
            return result;
        }else if (type == OBJ_BOOL){
            if (value == 0){
                return new ObjBool(false);
            }
            return new ObjBool(true);
        }else{
            return new ObjNull();
        }
    }
    Object* ObjReal::Cast(ObjectType type){
        if (type == OBJ_REAL){
            return new ObjReal(value);
        }else if (type == OBJ_STRING){
            return new ObjString(std::to_string(value));
        }else if (type == OBJ_INTEGER){
            return new ObjInteger((int)value);
        }else if (type == OBJ_BOOL){
            if (value == 0.f){
                return new ObjBool(false);
            }
            return new ObjBool(true);
        }else{
            return new ObjNull();
        }
    }
    Object* ObjBool::Cast(ObjectType type){
        if (type == OBJ_BOOL){
            return new ObjBool(value);
        }else if (type == OBJ_STRING){
            return new ObjString((value) ? "true" : "false");
        }else if (type == OBJ_INTEGER){
            return new ObjInteger(value ? 1 : 0);
        }else if (type == OBJ_REAL){
            return new ObjReal(value ? 1.0 : 0.0);
        }else{
            return new ObjNull();
        }
    }
    Object* ObjNull::Cast(ObjectType type){
        if (type == OBJ_BOOL){
            return new ObjBool(false);
        }else if (type == OBJ_STRING){
            return new ObjString("null");
        }
        return new ObjNull();
    }




    //operations
    Object* Object::Operation(Object* other, TokenType op, bool convert){
        if (!convert){
            if (other->type == type){
                return OperationSameType(other,op,true);
            }else{
                return new ObjNull();
            }
        }
        for (int i = 0; i < precedence.size(); i ++){
            if (type == precedence[i]){
                if (other->type == precedence[i]){
                    return OperationSameType(other,op,true);
                }else{
                    Object* newObj = other->Cast(precedence[i]);
                    Object* result = OperationSameType(newObj,op,true);
                    delete newObj;
                    return result;
                }
            }else if (other->type == precedence[i]){
                
                Object* newObj = Cast(precedence[i]);
                Object* result = other->OperationSameType(newObj,op,false);
                delete newObj;
                return result;
            }
        }
        return new ObjNull();
    }
    Object* Object::OperationSameType(Object* other,TokenType op, bool lhs){
        return new ObjNull();
    }
    Object* ObjString::OperationSameType(Object* other, TokenType op, bool lhs){
        ObjString* strOther = dynamic_cast<ObjString*>(other);
        if (op == PLUS){
            if (lhs){
                return new ObjString(value + strOther->value);
            }else{
                return new ObjString(strOther->value + value);
            }            
        }else if (op == EQUAL_EQUAL){
            return new ObjBool(strOther->value == value);
        }else if (op == BANG_EQUAL){
            return new ObjBool(strOther->value != value);
        }
        if (op == GREATER || op == GREATER_EQUAL || op == LESS_EQUAL || op == LESS){
            return new ObjBool(false);
        }  
        std::cout << "string failed" << std::endl;
        return new ObjNull();
    }
    Object* ObjBool::OperationSameType(Object* other, TokenType op, bool lhs){
        ObjBool* boolOther = dynamic_cast<ObjBool*>(other);
        //anything that doesnt directly involve bools is done in integer form
        if (op == AND){
            return new ObjBool(boolOther->value && value);
        }else if (op == OR){
            return new ObjBool(boolOther->value || value);
        }
        Object* selfInt = Cast(OBJ_INTEGER);
        Object* otherInt = boolOther->Cast(OBJ_INTEGER);
        Object* result = selfInt->OperationSameType(otherInt,op,lhs);
        delete selfInt;
        delete otherInt;
        return result;
    }
    Object* ObjInteger::OperationSameType(Object* other, TokenType op, bool lhs){
        ObjInteger* intOther = dynamic_cast<ObjInteger*>(other);
        if (op == PLUS){
            return new ObjInteger(intOther->value + value);
        }else if (op == MINUS){
            return new ObjInteger((lhs) ? (value - intOther->value) : (intOther->value - value));
        }else if (op == STAR){
            return new ObjInteger(value * intOther->value);
        }else if (op == SLASH){
            return new ObjInteger((lhs) ? (value / intOther->value) : (intOther->value / value));
        }else if (op == EQUAL_EQUAL){
            return new ObjBool(intOther->value == value);
        }else if (op == BANG_EQUAL){
            return new ObjBool(intOther->value != value);
        }else if (op == GREATER_EQUAL){
            return new ObjBool((lhs) ? (value >= intOther->value) : (intOther->value >= value));
        }else if (op == GREATER){
            return new ObjBool((lhs) ? (value > intOther->value) : (intOther->value > value));
        }else if (op == LESS_EQUAL){
            return new ObjBool((lhs) ? (value <= intOther->value) : (intOther->value <= value));
        }else if (op == LESS){
            return new ObjBool((lhs) ? (value < intOther->value) : (intOther->value < value));
        }
        return new ObjNull();
        
    }
    Object* ObjReal::OperationSameType(Object* other, TokenType op, bool lhs){
        ObjReal* intOther = dynamic_cast<ObjReal*>(other);
        if (op == PLUS){
            return new ObjReal(intOther->value + value);
        }else if (op == MINUS){
            return new ObjReal((lhs) ? (value - intOther->value) : (intOther->value - value));
        }else if (op == STAR){
            return new ObjReal(value * intOther->value);
        }else if (op == SLASH){
            return new ObjReal((lhs) ? (value / intOther->value) : (intOther->value / value));
        }else if (op == EQUAL_EQUAL){
            return new ObjBool(intOther->value == value);
        }else if (op == BANG_EQUAL){
            return new ObjBool(intOther->value != value);
        }else if (op == GREATER_EQUAL){
            return new ObjBool((lhs) ? (value >= intOther->value) : (intOther->value >= value));
        }else if (op == GREATER){
            return new ObjBool((lhs) ? (value > intOther->value) : (intOther->value > value));
        }else if (op == LESS_EQUAL){
            return new ObjBool((lhs) ? (value <= intOther->value) : (intOther->value <= value));
        }else if (op == LESS){
            return new ObjBool((lhs) ? (value < intOther->value) : (intOther->value < value));
        }
        return new ObjNull();
    }
    Object* ObjNull::OperationSameType(Object* other, TokenType op, bool lhs){
        return new ObjNull();
    }
    
}