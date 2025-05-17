#include "KObject.hpp"
using namespace KLang::KLangCompiled;
int main(){
	KObjFromLiteral(3)->Operation(KObjFromLiteral(2),OPERATOR_MULTIPLY)->Operation(KObjFromLiteral(5),OPERATOR_PLUS);
	return 0;
}