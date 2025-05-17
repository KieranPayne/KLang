#include "KObject.hpp"
using namespace KLang::KLangCompiled;

int main(){
	for (std::shared_ptr<KObject> i = KObjFromLiteral(0);std::dynamic_pointer_cast<KObjBool>(i->Operation(KObjFromLiteral(3),OPERATOR_LESS))->value;KObjFromLiteral(5))
	{
		print(KObjFromLiteral("hi"));
	}
	return 0;
}