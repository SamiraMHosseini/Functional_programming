# C++ Concurrent Programming
# Question: 

Is it clear what would happen if a thread blocked on a std::condition_variable receives a notification but the lock on the associated mutex is not yet released, 
and the lock will be released let's say 15 seconds later? Would the thread wait for the lock to be released or is the situation undefined?

# Answer:
It will continue to wait / wait_for until it can reacquire the lock.

When std::condition_variable::wait and wait_for returns (for whatever reason), the lock is held again, so you don't have to worry about that.

It can even return from wait without having gotten any notifications (spurious wake-ups) - but, no matter what, the lock is reacquired when the call returns.
If a thread blocks on a std::condition_variable and receives a notification but the lock on the associated mutex has not yet been released, 
the thread will wait until the lock is released before continuing execution. 
If the lock is not released, the thread will remain blocked and will not proceed to the next line of code.
This is the basic behavior of condition variables and mutexes in concurrent programming. 
The thread waits for the lock to be released to ensure that the shared data protected by the mutex is in a 
consistent state before it continues execution.
		
