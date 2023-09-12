#include <iostream> 
#include <thread> 
#include <mutex> 
#include <condition_variable> 
using namespace std; 

int count = 0; 
mutex mtx; 
condition_variable cv; 

void producer() 
{ 
	for (int i = 0; i < 5; i++) 
	{ 
		this_thread::sleep_for(chrono::milliseconds(10)); 

		// critical section (exclusive access to count) 
		unique_lock<mutex> lck(mtx); 
		count++; 
		cout << "count = " << count << endl; 

		// notify consumer if count is 1 
		// (notify_one unblocks one waiting thread) 
		if (count == 1) 
			cv.notify_one(); 
	} 
} 

void consumer() 
{ 
	// acquire lock 
	unique_lock<mutex> lck(mtx); 

	// wait until count != 0, then consume count 
	// (wait_for unblocks when notified) 
	cv.wait_for(lck, chrono::milliseconds(50), []{return count != 0;}); 
	cout << "Consuming count = " << count << endl; 
	count--; 
} 

int main() 
{ 
	thread producer_thread(producer); 
	thread consumer_thread(consumer); 

	producer_thread.join(); 
	consumer_thread.join(); 
}