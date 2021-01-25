#include "Singleton.h" 

std::unique_ptr<Singleton> Singleton::instance_ptr = nullptr;

Singleton::Singleton(){
    std::cout << this << " + \n";
}
Singleton::~Singleton(){;
    std::cout << this << " - \n";
}

Singleton& Singleton::instance(){
    if(Singleton::instance_ptr == nullptr){
        Singleton::instance_ptr = std::unique_ptr<Singleton>(new Singleton);
    }
    return *Singleton::instance_ptr;
}

void Singleton::calls(){
    std::cout << this <<" "<<++how_many_calls;
}