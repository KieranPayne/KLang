#pragma once
#include <map>
#include "Object.hpp"
namespace KLang{
    class Environment{
        public:
        //todo: add print function
        std::map<std::string, Object*> map;
        Environment(){
            
        }
    };
}