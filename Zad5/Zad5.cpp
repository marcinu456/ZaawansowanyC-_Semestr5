#include <iostream>

template <typename T, typename T2>
inline auto add1(const T& part1, const T2& part2)
{
	return part1 + part2;
}

template <typename T, typename T2>
inline auto add1(const T* const part1,const T2* const part2)
{
	std::cout << "pointer\n";
	return *part1 + *part2;
}

template <>
inline auto add1(const char* part1, const char* part2)
{
	std::cout << "const char\n";
	return std::string(part1) + part2;
}


int main() {
	//Zad5
	std::cout << "Zadanie 5\n";

	std::cout << add1<int>(5, 8) << "\n";
	int f1 = 3;
	float f2 = 4.5;
	std::cout << add1(f1, f2) << "\n";

	std::string s1 = "test", s2 = "lipot";
	std::cout << add1<std::string>(s1, s2) << "\n";

	std::cout << add1<const int, const float>(&f1, &f2) << "\n";

	const char str1[5] = "test";
	const char str2[6] = "lipot";


	std::cout << add1(str1, str2) << "\n";

}
