#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <numeric>
#include<cstdlib>
#include<ctime>

class FuelTank
{
private:
	unsigned int fuel_level;
	std::mutex fuel_mutex;
public:



	FuelTank(unsigned int _fuel_level):
		fuel_level(_fuel_level)
	{}
	unsigned int GetFuel(unsigned int volume)
	{
		std::lock_guard<std::mutex> lock(fuel_mutex);
		if (volume <= fuel_level)
		{
			fuel_level -= volume;
			return volume;
		}
		return 0;
	} 
};



class Engine
{
private:
	std::vector<std::shared_ptr<FuelTank>> fuelTank;
	unsigned int fuelExpendingTime;
	unsigned int fuelExpendingVolume;
	std::thread thread;
	std::mutex fuelTanks_mutex;

	void EngineWork()
	{
		std::this_thread::sleep_for(std::chrono::seconds(fuelExpendingTime));
		std::unique_lock<std::mutex> flock(fuelTanks_mutex);
		while (fuelTank.size()) {
			unsigned int volumeleft = fuelTank[0]->GetFuel(fuelExpendingVolume);
			if (volumeleft == 0) {
				fuelTank.erase(fuelTank.begin());
				std::cout << fuelTank.size() << " FuelTank left \n";
			}
			flock.unlock();

			std::this_thread::sleep_for(std::chrono::seconds(fuelExpendingTime));
			flock.lock();
		}

	}
public:
	Engine(unsigned int _fuelExpendingTime, unsigned int _fuelExpendingVolume) :
		fuelExpendingTime(_fuelExpendingTime), fuelExpendingVolume(_fuelExpendingVolume)
	{
		thread = std::thread(&Engine::EngineWork, this);
	}
	~Engine() {
		thread.join();
	}
	void addTank(std::shared_ptr<FuelTank> _fuelTank)
	{
		std::lock_guard<std::mutex> lock(fuelTanks_mutex);
		fuelTank.emplace_back(std::move(_fuelTank));
	}
};


int main()
{
	Engine engine0(5, 2);
	Engine engine1(1, 1);
	Engine engine2(2, 3);

	for (int i = 0; i < 10; i++) {
		unsigned int r = rand() % (20 - 10) + 10;
		std::shared_ptr<FuelTank> fuelTank = std::make_shared<FuelTank>(r);
		std::cout << r<<"\n";
		engine0.addTank(fuelTank);
		engine1.addTank(fuelTank);
		engine2.addTank(fuelTank);
	}

	return 0;
}

