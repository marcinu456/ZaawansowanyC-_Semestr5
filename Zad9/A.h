#pragma once
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

class A
{

private:
	char* bezsensu{ nullptr };
	size_t dl_tablicy{ 0 };

public:
	A(const std::string& name)  {
		std::cout << "constructor" << std::endl;
		dl_tablicy = name.size() + 1;//.length() + 1;
		bezsensu = new char[dl_tablicy];
		std::copy(name.begin(), name.end(), bezsensu);
		bezsensu[dl_tablicy - 1] = '\0';// name.begin();
		//strcpy_s(bezsensu, dl_tablicy, name.c_str());
	}
	//copy const
	A(const A& a){

		std::cout << "copy constructor" << std::endl;
		dl_tablicy = a.dl_tablicy;
		bezsensu = new char[dl_tablicy];
		memcpy(bezsensu, a.bezsensu, dl_tablicy);
		//strcpy_s(bezsensu, a.dl_tablicy, a.bezsensu);
	}

	//move const
	A( A&& a) noexcept { 
		std::cout << "move constructor" << std::endl;
		bezsensu = a.bezsensu;
		dl_tablicy = a.dl_tablicy;
		
		a.bezsensu = nullptr;
		a.dl_tablicy = 0;
	}

	
	const char* Get() const {
		return bezsensu;
	}

	~A() {
		std::cout << "Destruktorb" << std::endl;
		if (!bezsensu) return;
		else delete[] bezsensu;
		std::cout << "Destruktore" << std::endl;
		//delete bezsensu;
	}


};
