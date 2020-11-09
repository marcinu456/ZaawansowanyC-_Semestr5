#include <iostream>
#include "A.h"


//zad9
A copy(const A& copied) {
	std::cout << "copied const\n";
	return copied;
}

A copy(A&& copied) {
	std::cout << "copied const r value\n";
	return copied;
}



int main() {

	std::string strr = "string";

	std::string str = "0000string";
	std::cout << "test \n";

	A a1(str);
	A a2 = copy(a1);
	A a3 =copy(A (str));

	std::cout << "test \n";
	std::cout << a1.Get() << " A1 \n";
	std::cout << a2.Get() << " A2 \n";
	std::cout << a3.Get() << " A3 \n";
	
	printf("Address of x is %p\n", (void*)a1.Get());
	printf("Address of x is %p\n", (void*)a2.Get());
	printf("Address of x is %p\n", (void*)a3.Get());
	
	return 0;
}