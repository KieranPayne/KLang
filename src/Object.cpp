#include "Object.hpp"
#include <iostream>

namespace KLang{
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
    ObjReal::ObjReal(float value){
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
                float val = std::stof(value);
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
            Object* result = new ObjReal((float)value);
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
            return new ObjReal(value ? 1.f : 0.f);
        }else{
            return new ObjNull();
        }
    }
    Object* ObjNull::Cast(ObjectType type){
        return new ObjNull();
    }

}