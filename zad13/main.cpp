#include <iostream>
#include <future>
#include <mutex>
#include <string>

std::mutex g_i_mutex;
int threadId()
{
    static std::mutex m;
    static int number = 0;

    thread_local int localID = [&]() {std::lock_guard<std::mutex>lk(m); return number++; }();

    return localID;
}



void printThreadId(std::string str ) {

    const std::lock_guard<std::mutex> lock(g_i_mutex);
    std::cout << str << threadId() << "\n";
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

    std::async(Assynv, std::launch::async, 3);


    std::cout << "std::launch::async oraz std::launch::deferred;\n";
    std::async(std::launch::async, Assynv, std::launch::deferred, 3);
    return 0;
}