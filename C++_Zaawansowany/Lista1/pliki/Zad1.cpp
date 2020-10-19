//Autor Marcin Pietrzak
#include <iostream>
#include <array>
#include <vector>

template <typename T, typename T2>
inline auto add1(T part1, T2 part2)
{
	return part1 + part2;
}

template <typename T, typename T2, typename T3>
inline auto add2(T a, T2 b, T3 zwrotdonadawcy)
{
	return zwrotdonadawcy(a,b);
}


template <typename T = int, size_t Size=3>
class Wektor
{
public:
	std::array<T, Size> Tablica;

	using value_type = T;
	T& operator[](size_t el) { return Tablica[el]; }
	const T& operator[](size_t el) const { return Tablica[el]; }

};

template <typename T2, size_t Size, typename T>
T2 operator* (std::vector<T> const& VectL, const Wektor<T2,Size>& VectP)
{
	T2 wynikmnog = 0;
	for (size_t i=0;i<Size;i++)
	{
		wynikmnog+=VectL[i] * VectP[i];
	}
	return wynikmnog;
}

template <typename T2, size_t Size, typename T>
T2 operator* (const Wektor<T2, Size>& VectL, std::vector<T> const& VectP)
{
	return VectP * VectL;
}



int main()
{
	//Zad1
	std::cout << "Zadanie 1\n";

	std::cout << add1<int>(5, 8) << "\n";
	int f1 = 3;
	float f2 = 4.5;
	std::cout << add1(f1, f2) << "\n";

	std::string s1 = "test", s2 = "lipot";
	std::cout << add1<std::string>(s1, s2) << "\n";

	//Zad2
	std::cout << "\nZadanie 2\n";

	std::cout << add2(5, 8, [](int a, int b) {return a + b; }) << "\n";

	std::string s3 = "test", s4 = "lipot";
	std::cout << add2(s3, s4, [](std::string a, std::string b) {return a + b; }) << "\n";

	//Zad3
	std::cout << "\nZadanie 3\n";

	Wektor<int, 3> A = {1,3,3};


	std::cout << A.Tablica[1] << '\n';

	A.Tablica[1] = 1;

	std::cout << A.Tablica[1] << '\n';

	//Zad4
	std::cout << "\nZadanie 4\n";

	std::vector<int> v= {1,2,3};

	
	try 
	{
		
		if ((v.size() != A.Tablica.size()) || v.size() == 0 || A.Tablica.size() == 0)
		{
			throw "Error";
		}
		std::cout << A * v << '\n';
	}
	catch (...)
	{
		std::cout << "Niezgadzajaca sie lub zerowa ilosc skladowych\n";
	}
	


	return 0;
}