#include <iostream>
#include <future>
#include <mutex>
#include <string>

void printThreadId(std::string str ) {

    static std::mutex m;
    static int number = 0;

    thread_local int localID = [&]() {std::lock_guard<std::mutex>lk(m); return ++number; }();

    std::cout << str << number << "\n";  
}

void Assynv(std::launch policy, int Calls)
{
    if (Calls > 0)
    {
        std::future currentasscync = std::async(policy, Assynv, policy, --Calls);
        currentasscync.get();
    }
    printThreadId("Current thread id: ");
 
}


int main()
{

    std::async(Assynv, std::launch::async, 10);
    std::cout << "std::launch::async oraz std::launch::deferred;\n";
    std::async(std::launch::async, Assynv, std::launch::deferred, 10);
    return 0;
}