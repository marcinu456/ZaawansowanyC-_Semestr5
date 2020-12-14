#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <string>
#include <vector>



class Synchro {
    std::vector<std::function<double()>> taskList;
    std::vector<double> results;
    std::vector<std::thread> threads;
    void compute();
    std::mutex taskMutex;
    std::mutex resultMutex;
    std::mutex is_ready_mutex;
    bool is_ready= false;
    std::mutex mutex;
    std::condition_variable cv;
public:
    Synchro(int cores);
    void add_task(std::function<double()>);
    double average();
    void stop();
};

Synchro::Synchro(int cores)
{
    threads.reserve(cores);
    for (int i = 0; i < cores; i++) {
        threads.emplace_back(std::thread(&Synchro::compute,this));
    }
}
void Synchro::add_task(std::function<double()> task) {
    std::lock_guard<std::mutex> lock(taskMutex);
    taskList.push_back(task);
    cv.notify_one();

}
double Synchro::average() {
    if (results.size() != 0) {
        std::lock_guard<std::mutex> lock(resultMutex);
        double sum = 0.0;
        for (size_t i = 0; i < results.size(); i++) {
            sum += results[i];
        }
        return sum / results.size();
    }
    else return 0.0;
}
void Synchro::stop() {
    if (threads.size() > 0) {
        std::unique_lock<std::mutex> lock(is_ready_mutex);
        is_ready = true;
        lock.unlock();
        cv.notify_all();
        for (size_t i = 0; i < threads.size(); i++) {
            threads[i].join();
        }
        threads.clear();
         
    }
}


void Synchro::compute() {

    std::unique_lock<std::mutex> mlock(mutex);
    while (!is_ready || taskList.size() > 0) {
        if (taskList.size() > 0) {
            std::unique_lock<std::mutex> lock(taskMutex);
            std::function<double()> task;
            if (taskList.size() > 0) {
                task = taskList[0];
                taskList.erase(taskList.begin());
            }
           lock.unlock();
           double result = task();
           std::unique_lock<std::mutex> rlock(resultMutex);
           results.push_back(result);
           rlock.unlock();
        }
        else {
            cv.wait(mlock);
        }
    }
    mlock.unlock();
}

double test() {
    static double i = -1;
    i++;
    return 2+i;
}


int main() {
    int n = 5;
    Synchro synchro(n);

    for (int i = 0; i < n; i++) {
        synchro.add_task(test);
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "the average after 5 second numbers is: " << synchro.average() << "\n";
    synchro.stop();


    return 0;
}