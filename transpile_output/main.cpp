#include "KObject.hpp"
using namespace KLang::KLangCompiled;

int main(){
	while (std::dynamic_pointer_cast<KObjBool>((KObjFromLiteral(3)->Operation(KObjFromLiteral(5),OPERATOR_GREATER)))->value)
	{
		print(KObjFromLiteral("hi"));
	}
	return 0;
}