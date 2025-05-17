#include "KObject.hpp"
using namespace KLang::KLangCompiled;
int main(){
	std::shared_ptr<KObject> x = KObjFromLiteral(5);
	return 0;
}