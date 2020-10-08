//Autor Marcin Pietrzak
#include <iostream>


class Base
{
public:
	void FunctA()
	{
		std::cout << "Base: FunctA \n";
	}
	virtual void FunctB()
	{
		std::cout << "Base: FunctB \n";
	}
};


class Child : public Base
{
public:
	void FunctA()
	{
		std::cout << "Child: FunctA \n";
	}
	void FunctB()
	{
		std::cout << "Child: FunctB \n";
	}
};

int main() {

	Base base;
	Child child;
	Base* base_ptr;
	base_ptr = &child;

	base.FunctA();
	base.FunctB();
	std::cout << "\n";

	child.FunctA();
	child.FunctB();
	std::cout << "\n";

	base_ptr->FunctA();
	base_ptr->FunctB();
	std::cout << "\n";

	return 0;
}