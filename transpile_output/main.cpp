#include "KObject.hpp"
#include <iostream>
#include <chrono>
using namespace KLang::KLangCompiled;
void print(KObject x){std::cout << *x.Cast(KOBJECT_STRING).strVal << std::endl;}
KObject fib(KObject x){
	if ((x.Comparison(KObject(2),OPERATOR_LESS)).AsBool())
	{
		return KObject(1);
	}
	return fib(x.Arithmetic(KObject(2),OPERATOR_MINUS)).Arithmetic(fib(x.Arithmetic(KObject(1),OPERATOR_MINUS)),OPERATOR_PLUS);
	return KObject();
}

int main(){
	auto start = std::chrono::high_resolution_clock::now();
	print(fib(KObject(40)));
	auto stop  = std::chrono::high_resolution_clock::now();
    auto ms    = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	 std::cout << "function took " << ms << " ms\n";
	return 0;
}