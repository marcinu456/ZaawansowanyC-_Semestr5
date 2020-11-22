#include <iostream>
#include <omp.h>
int main()
{
#pragma omp parallel
//#pragma omp single
//#pragma omp master
//#pragma omp critical


	std::cout << "Witaj z watku nr " << omp_get_thread_num()+1
		<< " sposrod " << omp_get_num_threads() << "\n";
}

/*
1)
	a.Nie, z ka¿dym wykonaniem programu wynik jest inny, poniewa¿ praca jest rozdzielana pod poszczególne w¹tki
	b.Komunikaty wchodz¹ sobie w drogê, wynika to z tego, ¿e w¹tki wykonuj¹ pracê równolegle, niezale¿nie od siebiê i jeden w¹tek mo¿e skoñczyæ pracê zanim inny zd¹¿y to zrobiæ

2)
	#pragma omp single: Dany blok programu wykonujê siê tylko na jednym, niekoniecznie g³ównym, w¹tku, wykorzystujê tylko jeden dostêpny w¹tek
	#pragma omp master: Dany blok programu zawsze wykonujê siê na w¹tku g³ównym, przydatne jeœli chcemy ¿eby dany blok programu by³ wykonywany przez w¹tek g³ówny
	#pragma omp critical: wyniki programu nie wchodz¹ w siebie, s¹ wykonywane przez jedem w¹tek w danym czasie kolejnoœæ wykonywania nadal jest losowa, wyd³u¿a czas dzia³ania programu
*/