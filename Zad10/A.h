#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include <type_traits>
using namespace std;

class A
{

private:
	char* data{ nullptr };
	size_t dl_tablicy{ 0 };

public:
	A(const std::string& name) {
		std::cout << "constructor" << std::endl;
		dl_tablicy = name.size() + 1;
		data = new char[dl_tablicy];
		std::copy(name.begin(), name.end(), data);
		data[dl_tablicy - 1] = '\0';

	}
	//copy const
	A(const A& a) {

		std::cout << "copy constructor" << std::endl;
		dl_tablicy = a.dl_tablicy;
		data = new char[dl_tablicy];
		memcpy(data, a.data, dl_tablicy);
	}

	//move const
	A(A&& a) noexcept {
		std::cout << "move constructor" << std::endl;
		data = a.data;
		dl_tablicy = a.dl_tablicy;

		a.data = nullptr;
		a.dl_tablicy = 0;
	}


	const char* Get() const {
		return data;
	}

	~A() {
		std::cout << "Destruktorb" << std::endl;
		if (!data) return;
		else delete[] data;
		std::cout << "Destruktore" << std::endl;
	}


};


//zad10
template<class T>
A copy( T&& copied) {
	if constexpr (std::is_lvalue_reference<T> {}) {
		std::cout << "copied const \n";
		return copied;
	}
	else {
		std::cout << "copied const rvalue\n";
		return T(std::move(copied));
	}
}