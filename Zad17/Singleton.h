#pragma once

#include <iostream>
#include <memory>

class Singleton{
private:
    Singleton();
    static std::unique_ptr<Singleton> instance_ptr;
    int how_many_calls = 0;
public:
    ~Singleton();
    static Singleton& instance();

    void calls();

};
