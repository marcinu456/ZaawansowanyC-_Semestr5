#include <iostream>
#include <future>
#include <mutex>
#include <string>

 std::mutex g_i_mutex;
int threadId()
{
    static int number = 0;

    thread_local int localID = [&]() {return number++; }();

    return localID; 
}



void printThreadId(std::string str ) {
   
    std::lock_guard<std::mutex> lock(g_i_mutex);
    std::cout << str << threadId() << "\n";
}

void Assynv(std::launch policy, int Calls)
{
    if (Calls > 0)
    {
        auto currentasscync = std::async(policy, Assynv, policy, --Calls);

        currentasscync.get();
        printThreadId("Current thread id: ");
    }
    
}
 


int main()
{
    //Assynv(std::launch::async, 3);
    auto a=  std::async(std::launch::async, Assynv, std::launch::async, 10);
   
 // auto d = std::async(std::launch::async, Assynv, std::launch::deferred, 3); 
    return 0;
}