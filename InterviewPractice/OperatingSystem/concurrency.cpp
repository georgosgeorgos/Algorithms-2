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
    - Mutex 
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
