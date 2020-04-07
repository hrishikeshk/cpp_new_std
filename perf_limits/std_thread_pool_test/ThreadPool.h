#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <mutex>
#include <semaphore>

template<typename Task>
class ThreadPool{
	static ThreadPool* ms_instance;

private:
	ThreadPool(const ThreadPool& rhs);
	ThreadPool& operator=(const ThreadPool& rhs);

public:
	static ThreadPool* Instance(unsigned int sz);
	static void Release();
	
	void assign(Task* task);
private:
	ThreadPool(unsigned int sz);
	~ThreadPool();
	std::vector<std::thread> th_vec;

	std::semaphore sem_thr;
	std::queue<Task*> task_q;
	std::mutex mqueue;
	
	void thr_func();
	
	std::mutex mqfull;
};

#endif // THREADPOOL_H
