all: myProgram.out

myProgram.out: main.o libsingleton_static.a libsingleton_dynamic.so
	g++ -lm -o myProgram.out main.o -L. -lsingleton_static ./libsingleton_dynamic.so

main.o: main.cpp
	g++ -std=c++17 -c -g -Wall -pedantic -Werror -o main.o main.cpp

Singleton.o : Singleton.cpp Singleton.h
	g++ -std=c++17 -c -g -Wall -pedantic -Werror -fPIC -o Singleton.o Singleton.cpp

Calls1.o : Calls1.cpp Calls1.h
	g++ -std=c++17 -c -g -Wall -pedantic -Werror -o Calls1.o Calls1.cpp

libsingleton_static.a: Calls1.o Singleton.o
	ar rcs libsingleton_static.a Calls1.o Singleton.o

singleton_dynamic.o : singleton_dynamic.cpp singleton_dynamic.h
	g++ -std=c++17 -c -g -Wall -pedantic -Werror -o singleton_dynamic.o singleton_dynamic.cpp

libsingleton_dynamic.so : singleton_dynamic.o Singleton.o
	g++ -std=c++17 -g -Wall -pedantic -Werror -shared -o libsingleton_dynamic.so singleton_dynamic.o Singleton.o

clean:
	rm -f *.out *.o *.a *.so