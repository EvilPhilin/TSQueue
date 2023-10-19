#include "Headers/TSQueue.h"
#include <iostream>
#include <thread>

void writeToQueue(TSQueue<int>& q)
{
	std::thread::id id = std::this_thread::get_id();
	std::size_t seed = std::hash<std::thread::id>{}(id);
	std::srand(seed);

	for (int i = 0; i < 20; i++)
	{
		q.push(std::rand());
		std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 500));
	}
}

void readFromQueue(TSQueue<int>& q)
{
	// No need to worry about overhead because of sleep in cv
	while (true)
	{
		std::cout << q.pop() << " ";
	}
}

int main()
{
	TSQueue<int> q;

	std::thread(readFromQueue, std::ref(q)).detach();
	std::thread(readFromQueue, std::ref(q)).detach();

	std::thread w1(writeToQueue, std::ref(q));
	std::thread w2(writeToQueue, std::ref(q));

	w1.join();
	w2.join();
	return 0;
}
