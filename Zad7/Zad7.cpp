#include <iostream>

template<typename T, typename ...Argumenty>
auto add(T pierwszy, Argumenty... reszta) {
	if constexpr (sizeof...(reszta) == 0) 
		return pierwszy;
	else 
		return pierwszy + add(reszta...);
}

int main() {
	//Zad7

	std::cout << "test " << add(1, 1.0, 1.0f) << "\n";
	
	std::cout << "liczby " << add(8, 12, 5, 6.1f, 5.5) << "\n";

	std::string s1 = "test", s2 = "lipot", s3 = "twix";
	std::cout << "str " << add(s1, s2, s3) << "\n";
	return 0;
}