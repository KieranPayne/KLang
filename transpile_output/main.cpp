#include "KObject.hpp"
using namespace KLang::KLangCompiled;

int main(){
	std::shared_ptr<KObject> x = KObjFromLiteral(5)->UnaryOp(OPERATOR_MINUS);
	return 0;
}