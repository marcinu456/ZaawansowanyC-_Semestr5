#include <iostream>


template<typename T>
constexpr long double Hypercube(const T& a, const int& N)
{
	if (a >= 0 && N >= 0)
	{
		if (a == 0)
		{
			return 0;
		}
		else if (N == 0)
		{
			return 1;
		}
		int wynik = a;
		for (int i = 1; i < N; i++)
		{
			wynik *= a;
		}
		return wynik;
	}
	else
	{
		return -1;
	}
}

int main() 
{
	//Zad 6	
	std::cout << "objetosc hiperszesnianu o  a=3 i n=3 = " << Hypercube(3, 3) << "\n";

	std::cout << "objetosc hiperszesnianu o  a=6 i n=36 = " << Hypercube(6, 6) << "\n";

	return 0;
}