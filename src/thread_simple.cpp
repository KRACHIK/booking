#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <thread>
#include <string>


unsigned long long fib(const std::string & sFilePath)
{
	std::cout << sFilePath << "\n";

	//srand(time(0));
	int time = 10; //  rand() % 10;

	//std::this_thread::sleep_for(std::chrono::seconds(time));

	return time;
}

int main()
{
	const unsigned numberOfTask = 2;
	unsigned n = 100;
	std::vector<std::future<unsigned long long>> futures(numberOfTask);

	for (auto& f : futures)
		f = std::async(std::launch::async, fib, std::to_string(n));

	n = 30;
	for (auto& f : futures)
		std::cout << "fib(" << ++n << ") = " << f.get() << "\n";

	return 0;
}