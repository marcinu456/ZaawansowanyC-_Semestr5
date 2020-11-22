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
	a.Nie, z ka�dym wykonaniem programu wynik jest inny, poniewa� praca jest rozdzielana pod poszczeg�lne w�tki
	b.Komunikaty wchodz� sobie w drog�, wynika to z tego, �e w�tki wykonuj� prac� r�wnolegle, niezale�nie od siebi� i jeden w�tek mo�e sko�czy� prac� zanim inny zd��y to zrobi�

2)
	#pragma omp single: Dany blok programu wykonuj� si� tylko na jednym, niekoniecznie g��wnym, w�tku, wykorzystuj� tylko jeden dost�pny w�tek
	#pragma omp master: Dany blok programu zawsze wykonuj� si� na w�tku g��wnym, przydatne je�li chcemy �eby dany blok programu by� wykonywany przez w�tek g��wny
	#pragma omp critical: wyniki programu nie wchodz� w siebie, s� wykonywane przez jedem w�tek w danym czasie kolejno�� wykonywania nadal jest losowa, wyd�u�a czas dzia�ania programu
*/