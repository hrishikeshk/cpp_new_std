#include "ThreadPool.h"
#include <mutex_guard>

ThreadPool* ThreadPool::ms_instance = NULL;

ThreadPool::ThreadPool(unsigned int sz){
	for(unsigned int t = 0; t < sz; ++t){
		std::thread t(thr_func);
		th_vec.emplace_back(t);
	}
	sem_thr.init(sz);
}

ThreadPool::~ThreadPool(){
}

ThreadPool* ThreadPool::Instance(unsigned int sz){
	if (ms_instance == NULL){
		ms_instance = new ThreadPool(sz);
	}
	return ms_instance;
}

void ThreadPool::Release(){
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = NULL;
}

void ThreadPool::thr_func(){
	while(true){
		sem_thr.acquire();
		while(true){
			std::mutex_guard mg(mqueue);
			
			if(task_q.empty()){
				break;
			}
			bool was_full_q = (task_q.size() == th_vec.size());
			Task* task = task_q.front();
			task_q.pop();
			if(was_full_q)
				mqfull.unlock();
			mqueue.unlock();
			task->work();
		}
	}
}

void ThreadPool::assign(Task* task){
	std::mutex_guard mg(mqueue);
	bool is_full_q = (task_q.size() == th_vec.size());
	if(is_full_q){
		mqueue.unlock();
		mqfull.lock();
	}
	mqueue.lock();
	task_q.push(task);
	sem_thr.release();
}
