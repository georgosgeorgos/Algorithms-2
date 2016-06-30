//

Race Conditions on Data occur if these are true:
    - Data can be accessed by > 1 thread
    - Access can occur concurrently
    - Access mutates data

Accidental Data Sharing Using ThreadPools
{
    // main thread
    ThreadPool threadPool(numThreads);
    threadPool.Start()
    // make a variable from main thread
    int x = 5;
    pool.AddMethod(Callback(method1, &x));
    pool.AddMethod(Callback(method2, &x));
    // Problems:
        Main thread exits here and x is no longer usable
            Solution:
                Make x a shared_pointer, the smart pointer will make sure x exist 
                as long as things are pointing to it by reference counting
        Method1 and Method2 both modifies x at the same time
}

Prevent concurrent data access using Mutex
    - Mutex = Locks
        from:
            function(mutexForData, data) {
                mutexForData->Lock();
                accessData(data);
                mutexForData->Unlock();
            }
        to:
            function(mutexForData, data) {
                Mutex(&mutexForData); // constructor locks it
                accessData(data);
                // Destructor for Mutex unlocks it
          }
    - Optimization: ReaderLock 
        Can make reader locks such that more than 1 thread can have ReaderLocks 
        but it prevents threads from having WriterLock until all threads release their reader locks
        Only 1 thread can have access to a WriterLock at any time.
        This allows concurrent reads

Synchronization using:
    - Time (unreliable)
        thread1(methodWhichSleepsFor(100));
        thread2(methodWhichSleepsFor(1000));
        // Hope that base on probability, Thread1 runs before Thread2
    - Notification
        Each thread access a same data source called notification and writes to it, the threads can 
        read and write from it to synchronize
    - Barrier
        Barrier keeps a counter and a target value
        Each participating thread increments that counter, and Barrier returns true when counter reaches a value
        e.g.
        int numThreads = 3;
        Barrier barrier = new Barrier(numThreads);
        ...
        // threadN
        if(barrier->Block()) delete barrier; // barrier->Block will block until all numThreads has called barrier->Block()
                                           // only 1 thread will be in charge of deleting the block
        bool Barrier::Block() {
            // both numBlock and numExit are protected by Mutex
            this->numBlock--; // checks how many threads have called Block(), will release all of them once numBlock() == 0;
            this->lock->Wait(Condition(0 == this->numBlock)); // this makes the current lock wait until condition is true
            // now that the thread is done waiting, it can start decrementing it's exist
            this->numExit--; // keeps track of the number of which the threads exit
            return (this->numExit == 0); // only the last thread to exit will be true and will delete this barreir
        }
        Barrier::Barrier(int numThreads) : this->numBlock(numThreads), this->numExit(numThreads);
    - ConditionalVariables
      Blocks a thread until condition is satisfied until woken up by another thread
        // Thread 1: Sleeping Thread (Thread in charge of waiting until woken up by other thread)
        lock->Lock();
        while (!conditionIsTrue()) {
            conditionVariable.Wait(&lock); // wait will release the lock and block on this thread until it is signaled, then it re-acquires the lock
            // Here, it re-acquires the lock cause some other thread signals it
            // However, more than 1 thread that were waiting could have been signaled,
            // so we need to check the condition again, if condition is no longer true then this thread waits again.
            // This can happen if this thread was woken up, but then context switch occurs before it acquires the lock
        }
        // Condition variable is now true and we do have the lock, so now it's this thread's turn to do stuff
        // Do whatever you want with the lock
        ...
        // Done doing things, unlock it
        lock->Unlock(); // unlock it
        // Thread 2: The Waking Thread (Thread in charge of signalling sleeping thread to wake up)
        lock->Lock();
        // Do whatever
        ...
        setConditionToTrue(); // Make condition true first
        // Now signal another thread to wake up
        conditionVariable.Signal();
        lock->Unlock(); // unlock it for other threads to wake up
