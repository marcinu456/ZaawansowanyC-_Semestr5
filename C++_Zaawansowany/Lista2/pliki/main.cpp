#include <array>
#include <iostream>

template<typename T, T SIZE> // T SIZE?
constexpr auto table = [] { // constexpr? auto? []? brak ()?
	std::array<T, SIZE> result = {}; // std::array? = {}?
	for (T i = 0; i < SIZE; ++i)
	{
		result[i] = i * i;
	}
	return result; // typ wyniku?
}; // ()? ;?

int main()
{
	std::cout << table<int, 10>[6] // typ table? [6]?
		<< std::endl;
}