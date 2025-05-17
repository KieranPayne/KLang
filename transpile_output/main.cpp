#include "KObject.hpp"
using namespace KLang::KLangCompiled;
std::shared_ptr<KObject> test(std::shared_ptr<KObject> x){
	print(x);
	return std::shared_ptr<KObject>(new KObjNull());
}

int main(){
	std::shared_ptr<KObject> x = KObjFromLiteral(5);
	test(x->Operation(KObjFromLiteral(2),OPERATOR_MULTIPLY));
	return 0;
}