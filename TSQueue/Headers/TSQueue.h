#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class TSQueue
{
public:
	TSQueue();

	T pop();
	void push(T);

private:
	std::queue<T> q;

	std::mutex m;
	std::condition_variable cv;
};
#include "../Source/TSQueue.cpp"