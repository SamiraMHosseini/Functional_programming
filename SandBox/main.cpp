#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

struct SharedResource
{
	SharedResource() :
		cv_mutex(), cv(), counter(0)
	{

	}

	/*
	This mutex is used for three purposes:
	1) to synchronize accesses to counter
	2) to synchronize accesses to std::cerr
	3) for the condition variable cv
	*/
	std::mutex cv_mutex;
	std::condition_variable cv;
	int counter;
};

void waits(SharedResource& sharedRes)
{
	std::unique_lock<std::mutex> lk(sharedRes.cv_mutex);
	std::cerr << "Waiting... \n";
	while (sharedRes.counter != 1) 
	{

		/*
		
		If a thread blocks on a std::condition_variable and 
		receives a notification but the lock on the associated mutex has not yet been released, 
		the thread will wait until the lock is released before continuing execution. 
		If the lock is not released, the thread will remain blocked and will not proceed to the next line of code.
		This is the basic behavior of condition variables and mutexes in concurrent programming. 
		The thread waits for the lock to be released to ensure that the shared data protected by the mutex is in a 
		consistent state before it continues execution.
		
		*/
		sharedRes.cv.wait_for(lk,1s); 
		std::cerr << "Thread ID: " << std::this_thread::get_id() << " wakes up every 3 seconds.\n";
	}
	std::cerr << "...finished waiting." << "counter: " << sharedRes.counter << std::endl;
} //The lk object will be unlocked after this scope ends.

void signals(SharedResource& sharedRes)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lk(sharedRes.cv_mutex);
		std::cerr << "Notifying...\n";
	} // The lk object will be unlocked after this scope ends.
	sharedRes.cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(6));

	{
		std::lock_guard<std::mutex> lk(sharedRes.cv_mutex);
		sharedRes.counter = 1;
		std::cerr << "Notifying again...\n";
	
	sharedRes.cv.notify_all();
	std::this_thread::sleep_for(std::chrono::seconds(15)); //Adding for experimental purposes

	}// The lk object will be unlocked after this scope ends.
}

int main()
{
	SharedResource sharedRes;

	std::thread
		t1(waits, std::ref(sharedRes)),
		t2(signals, std::ref(sharedRes));
	t1.join();
	t2.join();
}

