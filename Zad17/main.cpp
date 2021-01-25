
#include <iostream>
#include "Singleton.h"
#include "Calls1.h"
#include "singleton_dynamic.h"



int main(){    
    Singleton::instance().calls();
    std::cout << " call from Singleton class\n";

    calls1();
    std::cout << " call from calls1()\n";

    instance().instance().calls();
    std::cout << " call from dynamic instance()\n";

    calls2();
    std::cout << " call from dynamic calls2()\n";

    return 0;
}

