#include <iostream>
#include <future>
#include <mutex>
#include <string>

void vvector(std::vector<double> v1, std::vector<double> v2, std::promise<double> &&curograf)
{
    try {
        if (v1.size() != v2.size()) throw std::runtime_error("wrong size");
        double wynik = 0;
        for (unsigned int i = 0; i < v1.size(); i++)
        {
            wynik += v1[i] * v2[i];
        }

        curograf.set_value(wynik);
    }
    catch (const std::exception& ) {
        curograf.set_exception(std::current_exception());
    }
}


int main()
{
    int N = 10;

    std::vector<double> v1{ 1, 2, 3,3 };
    std::vector<double> v2{ 3, 2,3};

    std::promise<double>* curograf = new std::promise<double>[N];

    std::future<double>* backtofuture = new std::future<double>[N];

    std::thread* threads = new std::thread[N];

    double result = 0;

    try
    {
        for (int i = 0; i < N; i++)
        {

            backtofuture[i] = curograf[i].get_future();
            threads[i] = std::thread(vvector, v1, v2, std::move(curograf[i]));
        }


        for (int i = 0; i < N; i++)
        {
            result += backtofuture[i].get();
        }
        std::cout << result << "\n";
       
    }
    catch (std::exception& e) 
    {
        std::cout << e.what();
    }
    for (int i = 0; i < N; i++)
    {
        threads[i].join();

    }
    delete[] curograf;
    delete[] backtofuture;
    delete[] threads;
    return 0;
}


