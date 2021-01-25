#include "singleton_dynamic.h"

void calls2(){
    instance().calls();
}

Singleton& instance() {
    return Singleton::instance();
}
