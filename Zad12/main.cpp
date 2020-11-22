#include <stdio.h>
#include <time.h>
#include <omp.h>
int main()
{
	const int N = 1000000000;
	int i = 0;
	double sum = 0;
	clock_t t0 = clock();
#pragma omp parallel for private(i) reduction(+:sum)
	for (i = N - 1; i >= 0; --i)
	{ 
	sum += 1.0 / (i + 1.0);
	}

	clock_t t1 = clock();
	printf("s = %g\n", sum);
	printf("t = %g\n", ((double)t1 - t0) / CLOCKS_PER_SEC);
}

/*
1)
� Czy wersja r�wnoleg�a daje ten sam wynik co szeregowa?
	Nie, wynik dla szerogowej jest r�wny 18.8079, dla r�wnoleg�ej 20.164

� Uruchom wersj� r�wnoleg�� na 1, 2, 4, 8 i 16 w�tkach, por�wnaj wyniki i czasy dzia�ania programu.
	1=18.8079 r_time=4.28, 2=18.8704 r_time=2.14, 4=19.0267 r_time=1.09, 8=19.4017 r_time=0.54, 16=20.164 r_time=0.29, czasy dzia�ania u�ytkownika praktycznie takie same, czas "real" si� zmniejsza

� Czy czas raportowany przez program funkcj� clock() jest czasem rzeczywistym
(wallclock) czy jakim� innym - je�li innym to jakim?
	Czas z funkcji clock() jest innym czasem, czasem procesora, zwraca czas procesora zu�ytej przez program, zwracana warto�� jest wyra�ana w tykni�ciach
� Dlaczego zawsze wychodzi inny wynik? Czy�by w kodzie by� b��d?
	Tak, jest to spowodowane niedok�adno�ci� float

� Czy czas raportowany funkcj� clock() nadaje si� do oceny przyspieszenia wersji
r�wnoleg�ej programu? Dlaczego?
	Nie poniewa� zwraca on liczb� cykli procesora, kt�ry za ka�dym razem jest taki sam lub zbli�ony

� Jaki fragment informacji wy�wietlanych komend� time (konkretnie: /usr/bin/time)
zawiera informacj� o liczbie u�ytych w�tk�w, a kt�ry - o rzeczywistym czasie
wykonywania si� programu?
	elapsed zawiera informacj� o czasi� rzeczywistym, pagefaults zawiera informacj� o u�ytuch w�tkach
	

*/