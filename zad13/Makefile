main.exe: main.obj
	link /DEBUG /OUT:main.exe main.obj

main.obj: main.cpp
	cl /std:c++17 /openmp /EHsc /c /Zi /W4 /WX /Fo:main.obj main.cpp