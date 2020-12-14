#include <iostream>
#include <future>
#include <mutex>
#include <string>

std::mutex g_i_mutex;
int threadId()
{
    //static std::mutex s_mutex;
    static int number = 0;

    thread_local int localID = number++;// [&]() {std::lock_guard<std::mutex> lock(s_mutex); return number++; }();

    return localID; 
}

void printThreadId(std::string str ) {
   
    std::lock_guard<std::mutex> lock(g_i_mutex);
    std::cout << str << threadId() << "\n";
}

void Assynv(std::launch policy, int Calls)
{
    std::future<void>* currentasscync = new std::future<void> [Calls];

    for (int i = 0;i < Calls;i++)
    {
       currentasscync[i] = std::async(policy, printThreadId, "Current thread id: ");
    }

    for (int i = 0; i < Calls; i++)
    {
        currentasscync[i].get();
    }

    delete[] currentasscync;
}
 

int main()
{
    std::cout << "std::launch::async\n";
    int  call = 3;
    Assynv(std::launch::async, call);
  
    std::cout << "std::launch::deferred\n";
 
    Assynv(std::launch::deferred, call);
  
    return 0;
}


