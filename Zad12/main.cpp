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
• Czy wersja równoleg³a daje ten sam wynik co szeregowa?
	Nie, wynik dla szerogowej jest równy 18.8079, dla równoleg³ej 20.164

• Uruchom wersjê równoleg³¹ na 1, 2, 4, 8 i 16 w¹tkach, porównaj wyniki i czasy dzia³ania programu.
	1=18.8079 r_time=4.28, 2=18.8704 r_time=2.14, 4=19.0267 r_time=1.09, 8=19.4017 r_time=0.54, 16=20.164 r_time=0.29, czasy dzia³ania u¿ytkownika praktycznie takie same, czas "real" siê zmniejsza

• Czy czas raportowany przez program funkcj¹ clock() jest czasem rzeczywistym
(wallclock) czy jakimœ innym - jeœli innym to jakim?
	Czas z funkcji clock() jest innym czasem, czasem procesora, zwraca czas procesora zu¿ytej przez program, zwracana wartoœæ jest wyra¿ana w tykniêciach
• Dlaczego zawsze wychodzi inny wynik? Czy¿by w kodzie by³ b³¹d?
	Tak, jest to spowodowane niedok³adnoœci¹ float

• Czy czas raportowany funkcj¹ clock() nadaje siê do oceny przyspieszenia wersji
równoleg³ej programu? Dlaczego?
	Nie poniewa¿ zwraca on liczbê cykli procesora, który za ka¿dym razem jest taki sam lub zbli¿ony

• Jaki fragment informacji wyœwietlanych komend¹ time (konkretnie: /usr/bin/time)
zawiera informacjê o liczbie u¿ytych w¹tków, a który - o rzeczywistym czasie
wykonywania siê programu?
	elapsed zawiera informacjê o czasiê rzeczywistym, pagefaults zawiera informacjê o u¿ytuch w¹tkach
	

*/