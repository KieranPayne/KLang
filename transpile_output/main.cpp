#include "KObject.hpp"
#include <iostream>
using namespace KLang::KLangCompiled;
void print(std::shared_ptr<KObject> x){std::cout << std::dynamic_pointer_cast<KObjString>(x->Cast(KOBJECT_STRING))->value << std::endl;}

int main(){
	print(KObjFromLiteral("starting"));
	for (std::shared_ptr<KObject> i = KObjFromLiteral(0);std::dynamic_pointer_cast<KObjBool>(i->Operation(KObjFromLiteral(100000000),OPERATOR_LESS))->value;i = i->Operation(KObjFromLiteral(1),OPERATOR_PLUS))
	{
	}
	print(KObjFromLiteral("done"));
	return 0;
}