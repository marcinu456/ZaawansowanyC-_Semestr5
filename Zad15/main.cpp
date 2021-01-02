#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <numeric>


class Synchro
{
	std::vector<std::thread> threads;
	std::vector<std::function<double()>> taskList;
	std::vector<double> results;

	std::mutex resultMutex; //mutex on vector of results
	std::mutex tasksMutex; //mutex on vector of taskList

	std::atomic<bool> bIs_ready = false;

public:
	Synchro(size_t threads_count)
	{
		for (size_t i = 0; i < threads_count; i++)
		{
			threads.push_back(std::thread(&Synchro::calculis, this));
		}

	}
	~Synchro() {};

	void add_task(std::function<double()> task)
	{
		std::lock_guard<std::mutex> lock(tasksMutex);
		taskList.push_back(task);

	}

	double  avarage()
	{
		std::lock_guard<std::mutex> rlock(resultMutex);
		double sumOfResults = std::accumulate(results.begin(), results.end(), decltype(results)::value_type(0));
		
		return (sumOfResults / results.size());
	}

	void stop()
	{
		bIs_ready = true;
		std::unique_lock<std::mutex> tlock(tasksMutex);
		while (taskList.size())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		tlock.unlock();
		for (auto& thread : threads)
		{
			thread.join();
		}

		threads.clear();
	}
private:

	std::function<double()> getTask()
	{
		std::lock_guard<std::mutex> lock(tasksMutex);
		if (taskList.empty())
		{
			return std::function<double()>();
		}
		else
		{
			std::function<double()> task = taskList.front();
			taskList.erase(taskList.begin());
			return task;
		}

	}


	void calculis()
	{
		while (!bIs_ready)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			
			std::function<double()>  task = getTask();
			if (task)
			{
				
				std::unique_lock<std::mutex> rlock(resultMutex);
				results.push_back(task());
				rlock.unlock();
			}
		}

	}
};

double test() {
	static double i = 0;
	i++;
	return 2 * (i);	
}

int main()
{
	size_t n = 40;
	Synchro synchro(105);
	for (size_t i = 0; i < n; i++)
	{
		synchro.add_task(test);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	synchro.stop();
	std::cout << "avarage: " << synchro.avarage() << std::endl;


	return 0;
}

