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
private:
	std::array<T, Size> Tablica;
public:
	
	Wektor() {
		Tablica = { 0 };
	}
	
	typedef T value_type;

	operator bool() const { return (Size != 0); }
	bool operator!() const { return (Size == 0); }

	T& operator[](size_t Size) { return Tablica[Size]; }
	const T& operator[](size_t Size) const { return Tablica[Size]; }

	size_t size() const{
		return Size;
	}
};

template <typename T, typename T2>
auto operator* (const T VectL, const T2 VectP)
{
	
	try {
		if (VectL.size() != VectP.size()) {
			throw (0);
		}
		else if (VectP.size() == 0 || VectL.size() == 0)
		{
			throw (1);
		}
		else {
			int wynik = 0;
			for (size_t i = 0; i < VectL.size(); i++)
			{
				wynik += VectL[i] * VectP[i];
			}
			return wynik;
			
		}
	}
	catch (int error) {
		if (error == 0)
		{
			std::cout << "nieprawidlowa wielkosc wektorow";
			return 0;
		}
		else if (error == 1)
		{
			std::cout << "wektory nie mogo byc 0 elementowe";
			return 0;
		}	
	}
	return 0;

	
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

	Wektor<int, 3> A;

	for (int i = 0; i < 3; i++) {
		A[i] = i;
	}

	std::cout << A.size() << '\n';

	//Zad4
	std::cout << "\nZadanie 4\n";

	std::vector<int> v= {1,2,3};

	std::cout << A * v << '\n';
	std::cout << v * A << '\n';
	return 0;
}