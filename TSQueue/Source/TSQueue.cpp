#include "../Headers/TSQueue.h"

// default constructor
template <class T>
TSQueue<T>::TSQueue() {}

template <class T>
void TSQueue<T>::push(T el)
{
	// Using unique_lock as a high level wrapper to work with cv
	// It also fulfills RAII
	std::unique_lock<std::mutex> lock(m);

	q.push(el);
	cv.notify_one();
}

template <class T>
T TSQueue<T>::pop()
{
	std::unique_lock<std::mutex> lock(m);

	cv.wait(lock, [this]() { return !q.empty(); });

	T element = q.front();
	q.pop();

	return element;
}