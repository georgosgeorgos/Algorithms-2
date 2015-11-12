Operating System Notes 
- Note: Rewrite into INT and upload (MUST REWRITE onto paper, CANT SHOW TRACES OF CODE
  FROM HERE, ALSO FOR ALL THE TLB STUFF, NEED PAPER FOR EXPLANATION) 

-----------------------------------------------------------------------------------------------------------------------------------------------------
// Table Index
-----------------------------------------------------------------------------------------------------------------------------------------------------
- Hardware Overview 
-----------------------------------------------------------------------------------------------------------------------------------------------------
	- CPU 
		- Program Counter
		- Instruction Register
		- Stack Pointer
		- Processor Status Word = Status Regiser
		- General Register 
	- Memory
		- Address Width 
	- IO Devices
		- Communication Between CPU and Devices 
		- Problems 
	- Interrupt vs Polling
-----------------------------------------------------------------------------------------------------------------------------------------------------
- OS Concepts
-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Isolation 
	- Abstraction 
		- Threads (CPU)
		- Virtual Memory (Physical Memory) 
		- Files (Disk) 
	- Interrupts vs Threads
	- Library Code vs Kernel Code
	- Problems 
	- Virtual Machine Monitor 

-----------------------------------------------------------------------------------------------------------------------------------------------------
- OS Related Hardware 
-----------------------------------------------------------------------------------------------------------------------------------------------------
	- CPU Modes 
	- Memory Management
		- Base and Limit Register (Different for each Process) (Stored in MMU state of the process) 
		- Paging MMU  (contiguous in virtual memory) 
	- Traps 
	- Exceptions
		- Segmentation Fault
		- Division by Zero
		- Hardware failure 
	- Interrupts
-----------------------------------------------------------------------------------------------------------------------------------------------------
- Threads vs Process
-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Program
		- Execution States
			- Address Space (virtual memory) => When program runs twice, it's address space is the same
				- Text/Code Region (read only) 
				- Data/Heap Region (global variables) 
				- Stack Region (Local variables and function calls (frame pointer, stack pointer)) 
			- OS-level state = Process Control Block 
	- Process
	- Program vs Process 
	- First Process vs Other Process
-----------------------------------------------------------------------------------------------------------------------------------------------------
- Thread Scheduling 
-----------------------------------------------------------------------------------------------------------------------------------------------------
	-thread state
	- scheduling policies
	- system call
		- thread_create()
		-thread_sleep
		-thread_wakeup
	- Scheduler Implementation
		- run, wait, ready queue 
		- Goals
		- Policies
			- Batch System
				- First come First Served
				- Shortest Job First (non-preemptive)
				- Shortest Remaining Time ( preemptive) 
			- Interactive System
				- Round Robin Scheduling
				- Static Priority Scheduling
				- Feedback Scheduling
	- Thread context Switch
	- Process Context switch 
	- Kernel thread vs User thread
	- Context Switch vs Mode Switch 

// Concurrency needs Mutual Exclusion (prevent race condition on shared data) and Synchronization (allows thread to synchronize some work together by waiting on condition) 
-----------------------------------------------------------------------------------------------------------------------------------------------------
- Mutual Exclusion 
-----------------------------------------------------------------------------------------------------------------------------------------------------
	- Requirements
		- Bounded Waiting
		- Progress
		- Timing
		- Mutual Exclusion 
	- Implementation 
		- Locks 
	- Problem: Locks are shared memory as well 
		- Interrupt Disabling (only uniprocessor) 
			- Multiprocessor uses different interrupts (won't be disabled) 
			- use this in uniprocessor 
		- Spin Locks (Atomicity on hardware) (only multiprocessor) 
			- Waste cpu on uniprocessor cause keep running useless instruction and thread holding lock does not release it
			- use this in multiprocessor 
		- Yielding Locks
			- check if didn't get, check again later 
			- will be long for T2 if critical section is short for T1 
		- Blocking Lock 
			- T1 tells T2 it is done executing 
			- takes a long time to execute (expensive) => Use spin lock if short critical section 
			- need spinlocks when adding and removing from queues but since those are short, spin lock is okay. 
				- need spinlocks when adding and removing from queues but since those are short, spin lock is okay. 
				- Note: Spin lock when blocking on multiprocessor, interrupt disabling when blocking on uniprocessor
			- need handle synchronization cause of lost wakeup 

Blocking Lock > Yielding Lock
	- when sleep occur for long time
	
Yielding Lock  > Blocking Lock	
	- Limits the number of wakeups based on the number of processes in system 
	- Thread is woken up frequently but sleep again cause condition is no longer true (e.g. broadcast when only 1 space available) 
			
- Synchronization 
	- Producer Consumer Problem
	- Using Monitors (wait() function and how it works) 
	- Using Semaphores
	- Semaphores vs Blocking Locks
	- Semaphores vs Monitors 

- UNIX Process
	- fork()
	- getppid()
	- getpid()
	- execv()
	- exit()
	- wait()
	- kill()
	- sigaction()	
- Memory Management 
	- Goals
	- Requirements
	- Problems
	- Techniques 
	- Compilation 
- Paging 
	- // TO BE FILLED 
- OS Support for Virtual Memory 
	- 
- Files
-----------------------------------------------------------------------------------------------------------------------------------------------------
// OS Related Hardware
-----------------------------------------------------------------------------------------------------------------------------------------------------
Traps 
- User program requesting OS instructions to run (caused by instructions in user code) 
- automatically jumps to pre-specified entyr point insturction in OS 

Exceptions
- Cause by software failures
	- Segmentation Fault (address not valid) 
	- Division by zero
	- Hardware failure (high temperature) 
	- User program tries to execute privileged instruction (killed by OS) 

Interrupts 
- Caused by external devices 
- Handler may have nothing to do with interrupted thread 
- For user program, none of interrupt handling is visible/known to them 
- Timing is important for devices 

Three main hardware components to support OS functionality: 
1. CPU Mode
2. Trap
3. MMU 

How is OS not a normal program? 
1. Can execute any instruction on machine 
2. Entered from different locations depending on events
3. Can be invoked simultaneously by multiple events (system call & interrupts) 
4. Not supposed to terminate

-----------------------------------------------------------------------------------------------------------------------------------------------------
// OS Concepts
-----------------------------------------------------------------------------------------------------------------------------------------------------
OS manages hardware resources providing
1. Abstraction
	- Virtual Machine abstraction : Each program thinks it has complete control over the machine and that i is the only one running
	- Programmers don't have to worry about hardware details 

2. Isolation
	- If program never issues system call, 
		-OS runs via timer interrupts (register timer interrupt before giving control to program) 
		-Disabling timer interrupts requires priveleged instructions (so programs can't disable it) 

OS handles these translation from software to actual hardware : 
	Hardware->SoftwareAbstraction
	1. CPU 		-> Thread
	2. Memory   -> Virtual memory 
	3. Disk		-> File

Threads
- Doesn't know actual number of physical CPU's (cores) 
	- Can be found using command ... 
- Thinks it accesses its own disks via files 
- Each thinks it has its own set of CPU registers  (saved by CPU state consisting of CPU registers, program counters, and stack pointers) 
- Advantages: 
1. Write concurrent program 
2. Number of threads != number of CPU cores
3. Hides latency (one thread waits, other runs) 

Interrupts vs Threads
- Interrupts run to completion, threads can be preempted 
- Interrupts run kernel code, Threads runs either user or kernel code 

Problems: 
1. Time sharing between programs 
	- Uses timer interrupts
2. Space sharing memory among programs
	- Use MMU to setup memory to ensure programs do not corrupt each other
3. Protection of programs from each other? 
	- Different memory to not corrupt each other's memory 
	- Timer interrupts so that all program runs 
4. Protection of hardware devices? 
	- Memory mapped devices so can't be run in user mode 
5. Protection of OS itself? 
	- Memory mapped OS memory so that cannot be accessed in user mode. 
	
Library Code vs Kernel Code
- Library code provides abstraction but not isolation. 
- Programs can jump to any instructions in library code and overwrite library code (bypassing any isolation library code tries to provide) 
	- Therefore, library code is read only memory and is normally within the regions of each individual program) 
	- So then, any changes to library code only affects that one program itself 
	- Library code is stored within the stack and heap of the program itself.
- Library code can't execute privilege instruction nor access kernel memory. 
- Kernel code can access privilege instruction and access kernel memory. 

Virtual Machine Monitor such as VMWare provide isolation and abstraction? 
It provides isolation but not any more abstraction than OS itself. 
	
Minimum number of privilege instructions? 
1, setting up the MMU (can put in location that is not accessible by user mode) 

-----------------------------------------------------------------------------------------------------------------------------------------------------
// Threads vs Process
-----------------------------------------------------------------------------------------------------------------------------------------------------
Program  = static file containing code and data
	- Describes how to perform computation
	- Has 3 execution states:
		- i)  CPU State (PC, SP, IR) 
		- ii) Memory (address space)
				- Text/Code Region (read only) 
				- Data/Heap Region (global variables) 
				- Stack Region (Local variables and function calls (frame pointer, stack pointer)) 
		- iii) OS-level state (a.k.a. Process Control Block) 
			The states are: 
			- CPU registers for thread switching
			- Thread ID to idenfity threads
			- Scheduling Parameters
			- Address space state (location of text, data, stack) 
			- File state
			- Network connection state
			
Process 
- 1 Address Space (virtual memory) 
Stack Thread 1 (each thread runs at different points of code, thus, instruction register is different) 
Stack Thread 2
.
.
.
Data // since each thread runs same data and code, can share the memory 
Code 
- Many threads (sharing that same 1 virtual memory) 
	- Process can start more threads using thread_create() system call 
- Started when user types the name of a program file to be executed. 

First Process vs Other Process
-First process is created by oses which runs in user mode, other process is created as a reslt of system call invoked by existing process. 

Single Processor
- Speed up only occurs if there is I/O computation waiting

Multi-Processor
- Can find regions of code that can be executed in parallel

Threads > Process
- Faster communication in reading and writing memory  (don't need issue system call to access shared memory) 
- Less memory needed since address space is shared (code and data specifically) 
- Thread switching is faster since no address space switching needed 

Threads < Process
- Writing memory affects other threads  (handle race conditions, deadlocks) 
- Need synchronization  (prevent lost wakeup) 

Program (a file of code and data) vs Process (in action)
- Program is a set of instructions and data, contained in a file 
- Process is a program loaded in memory and executing

Executable stores start address of a program so can know where to start executing 

Executable store end addrss of darta region => Heap starts there

Address Space of OS:
- Entire physical memory 

Who manages OS state when it is not running? 
- No one, the state is kept in memory inaccessible to user programs. It is accessible again when OS starts running either by timer interrupt or trap/exception system calls 

-----------------------------------------------------------------------------------------------------------------------------------------------------
// Thread Scheduling
-----------------------------------------------------------------------------------------------------------------------------------------------------
Thread Scheduling = scheduler decides which thread to run 
	- depends on:
		- Thread state
			i) Running
			ii) Blocked
			iii) Ready
			iv) Exited
		- Scheduling policies
			
	- uses system call: 
		i) thread_yield = current thread yields to CPU (voluntary =>preemptive) 
		ii) thread_sleep = current thread blocks for an event
		iii) thread_wakeup  = wake up a blocked thread 

Scheduler Implementation 
Different Queues exist for threads in different states: 
1. Run Queue = Ready List (running -> ready -> ready -> ...) 
2. Waiting Queue  (blocked -> blocked -> ...) 
3. Exited Queue (exited -> exited -> ...) 

Scheduler Goals: 
- Batch System => Long running programs, no interactive users, no time constraints
	- i) Maximize CPU utilization = max(% of time CPU is busy)
	- ii) Maximize Throughput = number of threads that complete execution per unit time
	- iii) Minimize Turn around time = min(time needed from program start to finish)

- Interactive System => Short running programs, Interactive Users, time constraints 
	- i) Minimize Response Time = time between receiving request to start producing output 
	- ii) Favor theads that wait for user input events
	- iii) Give each thread a fair share of CPU 
	- iv) Prevent starvation (search for 'Starvation' below for definition) 
	
Scheduling Policies: 
- Batch System
	- First come First Served
		- Start thread in order arrived 
	- Shortest Job First (non-preemptive)
		- Select thread with shortest running time
	- Shortest Remaining Time ( preemptive) 
		- Select thread with shortest remaining time to finish 
- Interactive System
	- Round Robin Scheduling
		- Runs each thread for a time slice until thread blocks in round-robin order
			- Shorter time slice => More interactive response but lower throughput 
	- Static Priority Scheduling
		- Each thread is assigned a priority
	- Feedback Scheduling
		- Priority of thread is altered based on thread behaviour
		- The more it uses the CPU , the higher the priority value increases => Priority decreases 
		- Helps IO bound processes run 
	- Unix Feedback Scheduling 
		- Goals; Allocate CPU fairly among threads
		- Give priority to threads that have not use much CPU recently (IO bounded thread) 
		
TurnaroundTIme = time from start to finish = wait time + processing time 
 CPu utilization => time that cpu is waiting for IO and not running anything
 CPU utilization = 1 = 100% if it is always executing 
 CPu allocation is 33% or 1/3 for each of the 3 available process. 
		
Scheduling policies subjected to starvation: 
1. Shortest Job First, Shortest Remaining Time, Priority Scheduling 
		
Multiprocessor Scheduling
	- Asymmetric Multiprocessing 
		- One processor runs all OS, IO code 
		- other processors run user code 
	- Symmetric Processing
		- All processor run OS and user code (more efficient , hard to implement) 
			- Processor Affinity
				- When process changes, cache has to be invalidated  (OS tries to keep running same processor) 
			- Load Balancing 
	
Thread Context Switch 
- OS suspend current tread and save CPU state for current thread
- OS restores next thread by restoring CPU State 
	 => Each thread must saved info. about it's state, and CPU state 
		
Process Context Switch
- Need switch address space by saving and restoring MMU state (base, limit registers) 
		=> each process need save info about MMU state 
- Also need save things similar to thread context switch 
- Also need invalidate entire TLB,

Thread_create Steps: 
1. Initialize memory, stack, PC, CPU state 
2. Set status to Ready and add to run Queue

Thread_termination states: 
1. Current thread terminate voluntarily using thread_exit (adds itself to the exited queue) , and then yield to other threads 
	- It does not free itself because if it did so, OS would not know which code to execute anymore and wouldn't yield to other threads	
2. Other thread frees its memory when they are running from the exited queue. 
3. Thread Exit is only called when thread is in running state so that it's read and write to IO may not be corrupted and only exits when it is truly ready 

Kernel Thread Vs User Thread 
Kernel thread can run in user mode and implement user threads
- user-level scheduler manages user thread 
- User thread are non-premptive but can be with the use of signals (timer signals in Lab 2) 
- OS is not aware of existence of user threads

User thread > Kernel Thread
- Flexible scheduling policy
- Cheap context switch since no system calls required 

User Thread < Kernel Thread
- Can't do blocking system call since only 1 kernel thread => Similar to 1 CPU only 
- Can't do I/O and computation at the same time since 1 kernel thread (not parallel) 

Note: Context switch generally refers to process context switch 

Context Switch Vs Mode Switch
- Context switch switches between threads 
- Mode switch switches the mode of the processor to kernel or user
- context switch = thread switch + mmu switch , mmu switch time > thread switch time		
		
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Mutual Exclusion
-----------------------------------------------------------------------------------------------------------------------------------------------------
Threads cooperate by sharing data via shared address space.
Critical Section = section of code that accesses shared data.
Each shared data has associated lock (thread sets lock before entering critical section and release lock upon leaving) 
Note: Lock and unlock are critical section themselves
Race condition = result of program execution depends on precise sequence of execution of threads. 
	- Prevent by:
		- i) Running 1 thread to completion at critical section (doesn't work with multiprocessor) 
		- ii) Synchronization of threads 
Atomic Operations = 2 operations are atomic when result is equivalent to sequential execution of some order 
Mutual Exclusion = Ensures only 1 thread at a time can access critical section 
- all other threads forced to wait on entry 
- when thread leaves critical section, another can enter 
- Mutual Exclusion requirements: 
	- i) Bounded Waiting: Each thread enters critical section within finite time 
	- ii) Progress: Thread cannot prevent another thread from entering critical section 
	- iii) Timing: No assumption made about speed or number of CPU's 
	- iv) Mutual Exclusion No 2 thread can be in critical section at the same time
		
- Problem: Locks are shared memory as well 
	- Interrupt Disabling (only uniprocessor) 
		- Multiprocessor uses different interrupts (won't be disabled) 
		- use this in uniprocessor 
	- Spin Locks (Atomicity on hardware) (only multiprocessor) 
		- Waste cpu on uniprocessor cause keep running useless instruction and thread holding lock does not release it
		- use this in multiprocessor 
	- Yielding Locks
		- check if didn't get, check again later 
		- will be long for T2 if critical section is short for T1 
	- Blocking Lock  
		- T1 tells T2 it is done executing 
		- takes a long time to execute (expensive) => Use spin lock if short critical section 
		- need spinlocks when adding and removing from queues but since those are short, spin lock is okay. 
			- Note: Spin lock when blocking on multiprocessor, interrupt disabling when blocking on uniprocessor
		- need handle synchronization cause of lost wakeup 
		
Deadlocks = every thread is waiting for an event that only another thread can perform 
Requirements for deadlock: 
	1. each resource is assigned to 1 thread
	2. theads can get more than 1 resource
	3. acquired resource are not preempted
	4. Circular wait 

Prevent Deadlock: 
	1. Acquire locks in same order (number the locks) 
	2. Release lock if next lock not available 
		Problem: can cause live lock (too much time locking that no actual work is done) 

Starvation => some threads no work is performed cause resources needed are constantly being used
	- Solve by using FIFO queue whenever thread needs to wait on condition (all threads get to make progress) 
Live lock => no work done on all threads  (example: Interrupt keeps executing to context switch all the time that no actual work gets done) 
    - Cause both threads keeps releasing and acquiring their locks so context
      switches happen all the time instead of actual thread code. Prevent by
      prioritizing threads, making threads with lower priority release locks
    and higher priority threads not release locks. 
	- Solve by making sure each thread runs for a long enough time before switching to other threads 

Need disable interrupts (for uniprocessor) for thread_yield because it accesses shared data which are the run and wait queues. 

Can locks be implemented by reading and writing a binary variable? 
No, reading and writing binary variable itself needs to be atomic 
No, because the entire variable which holds 32 different locks is actually 1
lock itself, so you cant really use all 32 locks simultaneously as it is just
1 lock. 
		
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Synchronization 
-----------------------------------------------------------------------------------------------------------------------------------------------------
Synchronization => thread needs to wait until some condition is true
Example Problem: Producer Consumer Problem (server reads data and put into buffer, threads read from buffer and send IO to respective client) 
Producers adds data to buffer
Consumers remove items from buffer
Synchronization => Suspend producer if buffer full 
				   Suspend Consumer if buffer empty 
Need take care of: 
1. Locking shared lock 
2. while loop to check conditions again
3. Thread sleep and wakeup to prevent busy spinning
But if lock then sleep may cause deadlock
But if unlock then sleep may cause race condition => Lost wakeup 
Therefore, need blocking lock and sleep to be atomic (use either disable interrupt (uniprocessor) or spin lock(multiprocessor) to unlock and sleep, 
and only re-execute once woken up and try to require the lock before exiting the wait func() 

Basically entire above is grouped into the wait function 
wait_func(cv, lock)
{
	disable interrupt
	release(lock)
	sleep(cv)
	// woken up by signal 
	acquire(lock) // note: Will sleep here again until lock is acquired 
}

Thus, use monitors and ignore everything above cause it doesn't work. 
use cv_wait(cv,lock) => Wait on condition variable and release lock at same time. 
// Also need spin locks or interrupt disabling cause modifying run queue itself is a shared data structure 

Monitors: 
	- Only one thread access monitor data at a time => Each monitor is associated with a lock
	- One or more condition variables used for synchronization 

cv_create() = create condition variable
	- has a wait queue
	- 
cv_destory(cv) = destroy condition variable
cv_wait(cv,lock) = wait on this condition variable and release lock atomically 	
cv_signal(cv, lock) = signal 1 thread waiting on v) 
cv_broadcast(cv, lock) = wake up all threada waiting on condition. 

Note: the function outside this has to only call wait if the condition is not available  and this function automatically sleeps and wakes up upon signaled. 
wait(notFull) => sleeps on condition and release lock atomically by releasing lock using turning off interrupt or spin locks 
				// also makes sure it reacquires the lock before waking up 

Semaphore - integer that is incremented or decremenet 
P(sem) => decrement
V(sem) => incremement

Semaphore Vs Lock 
1. Semaphore can be called in any order 

Semaphore vs Monitor
1. Semaphore doesn't wait if resource not available, 
2. Signal can be lost in monitor but V is not lost , 
	it is not lost because V updates a data that can later be read by P whereas signal only executes on thread if it is currently waiting. 
3. Multiple threads can access semaphore as long as there are still spaces,
whereas only one thread can access a single monitor at any given time. 
4. Monitor is shared by each thread signalling each other a variable is
available, Semaphore is checked by checking that there are extra resources for
a semaphore available to be shared. 

Blocking Semaphore
=> Semaphore with sleeping 
=> Disable interrupt and then sleep() => Next thread will enable interrupt again

Need place P & V correctly cause wrong ordering can cause race conditions or deadlock. 

-----------------------------------------------------------------------------------------------------------------------------------------------------
// Hardware Overview 
-----------------------------------------------------------------------------------------------------------------------------------------------------
CPU 
- Program Counter = holds memory address for next instruction 
- Instruction register = holds instruction currently being executed
- Stack Pointer = holds address of memory for accessing stack 
- Status Register = Control bits that affect program execution 

Memory 
- Address Width = number of bits that represent address (eg: 32 bit or 64 bit processor) 

I/O Devices
- Communication occurs via: 
	i) Special IO Instructions
	ii) Memory mapped IO location to be read and written 
-Problems: 
	- CPU and devices compete for memory (handled by memory controller) 

Interrupt vs Polling
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Memory Management
-----------------------------------------------------------------------------------------------------------------------------------------------------
Memory Management Goal
1. Low Memory Overhead : Program can use as much memory as possible 
2. Low Performance Overhead : CPU executing most of the time

Memory Management Requirements 
1. Isolation: Different program cannot access each other memory 
2. Abstraction: Each program  thinks there is infinite memory 
3. Sharing	: Different programs may share memory/code (Example: <stdio.h> library) 

Virtual Memory = Address seen by CPU 
- Abstraction of physical memory 
- each thread thinks it has its own memory and accesses entire address sapce 
Physical Memory = Address seen by memory 

Memory Management Unit => Translate Virtual Memory -> Physical memory 

Problems:
1. Internal Fragmentation : Memory allocated is not fully used
2. External Fragmentation: Enough memory available but it is not fully used. 

Memory Management Techniques
1. Bitmaps : 1 bit to determine if allocated or not
			 x bit to store memory 
			Thus, total overhead is 1/(1+x) , example: Chunk Size = 4kb => Total overhead = 1 / (1 + (4*1024*8))	
2. LinkedList of memory: P->H->P->H ..., H = hole (available), P = process (in use) 
	Searching for empty slot: 
	i) First Fit : First to fit from 0 
	ii) Best Fit : Smallest memory to fit
	iii) Quick Fit  : Pre-allocated memory of different size to fit different regions (More efficient but higher complexity) 
	iv) Worst Fit : Biggest Memory to fit
	v) Next Fit: Next memory available that fits
	Note: Keep holes sorted by memory address allows easy combination of holes 
Compilation 
- Done on virtual memory: 
	- use paging systems (Memory appears contiguous)
	- Physical memory not accessible by programs 
	Note: Address translation done in hardware as happens faster 
	Compiling => Address from 0-> X 
	Linking => Address from 0 -> C -> C+X (C is memory used by other files in program) 
	Loader => Address from 1000->1000+C -> 1000+C+X (1000 is starting address on actual physical memory) 
	
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Paging
-----------------------------------------------------------------------------------------------------------------------------------------------------
Memory management problem is that virtual memory is contiguous, making it hard to grow memory due to external fragementation. 

Paging = A memory management system that translate contiguous virtual address to non-contiguous physical address
- Paging MMU maps each page to a frame => (Page Size = Frame Size) 
- Pages are contiguous, frames are not 
	- Therefore, need to know where the frame is for each page 

Virtual addr => Contiguous fixed size pages 
Page size = 2^n = Frame Size (frame is actual size on hardware needed) 
=> n = size of offset 

Benefits of Paging: 
1. No need to copy programs to a different location when it grows/shrinks in memory 
2. No external fragmentation since can always get a new frame for the same process. 
3. Internal fragmentation < 1 frame size per process since the entire frame is always used up before a new frame is allocated. 

Virtual Memory Address 
	Assuming 32 bit address width system with max physical memory size of 2^M , 32 bit address width => Address space size = 2^32 
	min(32,M) - n 		, n  // eg. 32 bit address width with 1 GB = 2^30 max. physical memory size => 30-n, n : 30-n => Page number 
	page number, offset for the page (offset = n bits => page size = frame size = 2^n) 
	Number of pages = 2^(min(32,M) - n)
	Note: n increases => lower overhead for each page table, overhead = memory needed to allocate page table , overheadPerProcess = PageTableSize
		  n decreases => Lower internal fragmentation
			Trade off between overhead to store page table and amount of internal fragmentation. 
			
			
Page Table = Translation information from page number to frame number is stored in Page Table 
	- Each page table entry is 1 word = 2^2 = 4
	- Contains frame number and control bits (valid, dirty, writeable) 
	- Implementation: 
		1. Linear Page Table 
			- Page Size = 2^12 = Frame Size => number of offsetbits = 12 => n = 12 
			- Virtual address given is = 0x1003a6f
			- // Need get offset value  to index to the right position in page (byte addressable) 
			offset = virtualAddress & 0xfff // get low 12 bits 
			pageNumber = virtualAddress >> 12 // get high order min(32,M) - n bits to know location in frame using pageTable 
					// Note: pageNumber != frameNumber, pageNumber is used as an index in Page Table to get frameNumber stored 
			// Look up frameNumber using page table. Note: NOW Is when Page Table comes into play 
			frameNumber  = pg_table[pageNumber].frame = 0x30 // assume it is 0x30  // note: You are getting this value from physical memory since it's contents are
																					// stored in physical memory 
			// Get actual location in physical address using frameNumber and offset to be byte addressable
			PhysicalAddress = (frameNumber << 12) | offset // shift to upper min(32,M) - n bits and OR it with the offset for low order n bits , where n = 12 in this case
			//																					 Since each page table entry is assumed to be of size 4 (1 word) 
			// Now you need to access physicalMemory at the PhysicalAddress location a 2nd time 
			
			Page Table Size = numberOfPageTableEntries * sizeOfPageTableEntry = 2^(min(32,M)-n) * 4  = 2^20  * 4 = 2^22 = 4MBytes for each process memory overhead to store pageTableSize
			Advantage: Fast access in comparison to other implementation methods (although need 2 memory accesses) 
			PROBLEMS: 
			i) Page table is too big (2^22) => Store in memy instead of mmu 
				- This means need 2 memory accesses to access actual memory 
					- 1 to access page table (e.g. page_table[pageNumber])
					- 1 to access memory (contents of actual PhysicalAddress) 
					=> It is slow
					-Solution: 
						Cache the page table entries => only 1 memory access needed since cache is fast. 
						// This cache is called Translation Lookahead Buffer  = a cache for Page Table Entries NOT data
			ii) Overhead is TOO LARGE = 2^22 = 4MBytes is the amount of memory needed for each process. Especially when frameSize = 2^12 
				// This means you need 2^22/(2^12) = 2^10 number of frames just to store the overhead needed to construct a pageTable. 
				Therefore , need to save space by reducing overhead (however increasing internal fragmentation) 
				Also, want to be able to be efficient in finding entries quickly 
				Therefore: Multi-Level Page Table
		2. Multi-Level Page Table (implemented with multiple smaller LinearPageTable that points to the next PageTable and only last one pointing to the actual frame) 
			- Use a tree data structure instead of an array 
			eg: 2-Level Page Table  
				// (referring to the same type as above, where each entry is 1 word (4 bytes) , (Note: Everything is in bytes and not bits in page-related calculation)
				// Page size = 2^12, n = 12, 32 bit system, size of physical memory > 2^32
			// => There are 2
			First Level = page table uses the first 10 bits
			Second Level = page table uses next 10 bits 
			Offset = remaining n = 12 bits 
			Given Virtual Address = 0x1003a6f
			offset = virtualAddress & 0xfff // get low order 12 bits 
			PageNumberOneIndex = virtualAddress >> 22 // get first 10 bits to index into first page table to get memorylocation of second page table 
													// Note: Memory location of everything must be shifted by offset! 
			PageNumberTwoIndex = (virtualAddress >> 12) & 0x3ff // get next 10 bits to index into second page table to get memory location of frame number
			FirstPageTable = page_table_register // base of page table
			SecondPageTable = FirstPageTable[PageNumberOneIndex].frame << 12 // to get value for accesssing 2nd page table
			FrameNumber = SecondPageTable[PageNumberTwoIndex].frame  // you can shift by 12 here but you decided to shift by 12 when calculating physical address below 
			PhysicalAddress = (FrameNumber << 12) | offset
			Advantage: Save a lot of overhead compared to Single-Level Page Table 
					- cause not all pages in page tbale are allocated
					- It only allocates the 2nd level pages if the valid bit is 1 in the firstLevelPage  
			Disadvantage: Now need 3 memory accesses (1 for FirstPageTable, 1 for 2ndPageTable, 1 for physical memory itself) 
		Disadvantage of Both (single-level and multi-level): 
			Note: Both single and multi-level page allocates 1 page table entry per page => Overhead grows with virtual address space size 
			e.g. 
			Assume 64 bit address width => 64 bit processors => pageTableEntrySize = 8 byte 
			Page size = 2^12 = 4KBytes
			=> Virtual Address Space = 2^64/(2^12) = 2^52 number of pages
			Linear page table needs 2^52 * (8byte) = 2^55 bytes per process is needed => THIS IS TOO LARGE FOR MEMORY 
			Even Multi-Level page table can have a similar problem (18,18,12) -> Each pageTableLevel needs 2^18/(2^12) number of frames to store it 
			Therefore, to solve this, use inverted page table 
		Overhead = sizeToAllocateOnePageTable/totalSizeOfPhysicalMemory 
			e.g. 
			64 bit processor => 8byte pageTableEntry 
			Page Size = 2^12 = 4KByte
			Memory Size = 2^33 = 8GByte 
			VirtualAddressSpace = 2^(33-12) = 2^21 = 2Mb per process 
			Overhead = 2Mb/8GB = 2^(21-33) = 2^(-12) => 0.2% (low overhead) 
			
			Thus, use inverted page table 
			
		3. Inverted Page Table 
			- Similar to a hashTable
			- Stores one entry for every frame that exists in physical memory 
			- Frame is stored as index to InvertedPageTable
			- each entry stores the page that it links to as well as the associated thread (multiple thread can point to same page), as well as nextFrameNumber to handle Collisions
				// However, the hash function has to hash the same page to the same location on frame 
				// => 0(1) search time! 
			
			e.g. 
				ThreadID = 5, VirtualAddress = 0x23abc
				page = VirtualAddress >> 12  // get rid of offset 
				
				hash(page, TID) = x // x is provided by hash function ,   0 <= x <= numberOfFrames-1
				// Collisions are resolved by going into index shown by nextFrameNumber. If no nextFrameNumber => No more collision, store info there. 
				
			- Disadvantage: 
				- Contiguous virtual memory is no longer contiguous on frames => poor caching 
				- Hash function has to be good to prevent many collisions. 
				- Sharing memory across processes is complicated since if 2 pages were mapped to the same frame, then they must hash to the same value. 
			
	-Improving Implementation:  Since many memory accesses and collisions, cache recently used pageTableEntries instead, also for memory protection. 
		Memory Protection 
			- Each memory partition needs different protection
			- Text -> Read, execute (no write) 
			- Stack and Data -> Read, write (no execute) 
			=> Page table entry itself has protection bits
			- Generates rpotection fault when read-only pages is written 
			- Speeds up page-level protection enforecement 
			=> Cache protection bits in TLB 
		Translation Lookaside Buffer  = a cache for page table entry
			Purpose: Speeds up address translation and allows memory protection. 
			- If page table entry in TLB, is valid, and accessible to user => TLB Hit (has protection bits for memory protection) 
			- otherwise, TLB Miss 
			- If TLB Miss , need methods to cache it into TLB for later use
				// if TLB was fully filled, need to replace depending on the TLB Replacement Policy 
			- TLB cache invalidate 
				- need invalidate entire TLB if context switching occurs since each thread has their own set of page table entry 
				- Method 1 =  Clear TLB: Clear TLB with a clearBit
				- Method 2 = Tagged TLB: Keep track of which threadID is using, therefore,  if threadID invalid => TLB Miss as well. 
Disadvantage of Page Table: 
- Have to allocate memory for entire process => If process memory requirement larger than physical memory available => Can't run process
- If too many concurrent process => Too much memory needed 
Therefore, use Demand Paging 
		
How does processor locate page table? 
	- Using dedicated register called page table register 

Why are inverted page tables not used for 32 bit architectures
	- Multi-level page tables work well as not as much overhead 
		2^32/ (2^n) instead of  2^64/(2^n) 

Benefits of Hardware-Managed TLB? 
	Fast handling of TLB miss

Benefits of Software-Managed TLB? 
	Flexibility in TLB miss handling 

Protection Fault? 
	Page access is inconsistent with protection bits associated with page on TLB. 
	
		
		// Illustration of Linear Page Table
		                 page number           offset      
                +---------------------+-----------+
      virtual   |      20 bits        |  12 bits  | 
      address   +----------+----------+--------+--+ 
                           |                   |    
      +--------------------+  0x4              |    0xa6f
      |                                        |    
      |                                        |    
      |         +---------------+-+            |
      |   2^20-1|               | |            |
      |         +---------------+-+            |
      |   2^20-2|               | |            |
      |         +---------------+-+            |
      |         |               | |            |
      |         +---------------+-+            |
      |         |               | |            |
      |   index +---------------+-+            |
      +-> 0x1003|     0x30      |1|----+       |    
                +---------------+-+    |       |
                |               |0|    |       |
                +---------------+-+    |       |
               2|               | |    |       |
                +---------------+-+    |       |
               1|               | |    |       |
                +---------------+-+    |       |
               0|               | |    |       |
                +---------------+-+    |       |
                 frame number  valid   |       |
                    18 bits            |       |
                              +--------+       |
                              |                |
                              V                |
                       frame number    offset  V
                      +---------------+-----------+
      physical        |       0x30    |   0xa6f   | 
      address         +---------------+-----------+
                           18 bits       12 bits
		
		// Illustration of 2-Level Page Table 

                 page number           offset
                +---------------------+-----------+
      virtual   |  10 bits | 10 bits  |  12 bits  |
      address   +----+-----+----+-----+-----------+
                     |          |
                 0x4 |          | 0x3
        +------------+          +------------+
        |                                    |
        |        Top-level page table        |          Second-level page table
        |       +---------------+-+          |         +---------------+-+
        | 2^10-1|               | |          |   2^10-1|               | |
        |       +---------------+-+          |         +---------------+-+
        | 2^10-2|               | |          |   2^10-2|               | |
        |       +---------------+-+          |         +---------------+-+
        |       |               | |          |         |               | |
        |       +---------------+-+          |         +---------------+-+
        |       |               | |          |         |               | |
        | index +---------------+-+          |         +---------------+-+
        +------>|     0x10000   +1+----+     |         |               | |
                +---------------+-+    |     |   index +---------------+-+
                |               |0|    |     +-------->|    0x30       |1|--+
                +---------------+-+    |               +---------------+-+  |
               2|               | |    |              2|               | |  |
                +---------------+-+    |               +---------------+-+  |
               1|               | |    |              1|               | |  |
                +---------------+-+    |   physical    +---------------+-+  |
               0|               | |    |   address    0|               | |  |
      PTR ----> +---------------+-+    +- 0x10000000 ->+---------------+-+  |
                    frame nr                                frame nr        |
                    18 bits                                 18 bits         |
                                                                            |
                              +---------------------------------------------+
                              |
                              V
                       frame number    offset
                      +---------------+-----------+
      physical        |       0x30    |   0xa6f   | 
      address         +---------------+-----------+
                           18 bits       12 bits


-----------------------------------------------------------------------------------------------------------------------------------------------------
// OS Support for Virtual Memory 
-----------------------------------------------------------------------------------------------------------------------------------------------------		
		
- OS Support for Virtual Memory 


Demang Paging 
- Allows running programs that reside in memory partially 
- Processes that require more memory than available physical memory can run as long as current memory needed does not exceed available physical memory 
- Load memory as they are accessed instead of loading entire memory when program is started. 
- Invalid Page => Page whose Page Table Entry is invalid 
- Page Fault => Trying to access an invalid page. (Page Fault is an Exception) 
	=> CPU generates exception
	   OS evict pages if no frames available 
	   OS handles it by allocating frame to page and making it valid
	   OS restarts the program
	   
Overview 
TLB Miss -> Load PTE from Page Table into TLB 
	// If PTE doesn't exist
	Page Fault -> Load frame for page 
		// If frame not available
		Swap Handler -> Evict a page to disk and return freed frame 
		
TLB Miss: Goal => Load PTE from page table into TLB 
	Hardware Handler => OS not involved
	Software Handler => CPU Generate TLB miss fault,OS runs handle code 
		- Handler gets 2 inputs:
			- i) Virtual address of faulting access 
			- ii) Type of fault (read miss, write miss, protection fault) 
		- Handler uses virtual address to look up page table for PTE
			- If PTE is valid, and has consistent protection bits  (page was accessed in past but evicted from TLB) 
				- load PTE into TLB 
				- If replacing an existing TLB entry and it is dirty, 
					update the dirty bits in entry 
					Synchronize PTE associated with TLB entry being replaced 
			- PTE is invalid => Generate Page Fault
				On Page Fault: Goal: PTE is invalid, allocate frame for faulting page, map page to frame
				(OS handler) 
					On errors: OS kills thread and runs another and parent observes that child has segmentation fault. 
						ErrorNotMapped
							If faulting address not mapped: return error
						ErrorInconsistentProtectionFlags 
							If fault type inconsistent with region's protection flags, return error 
					If no error, 
						allocates frame and page table entry if needed for multi-level
						If no frame to allocate, call swap handler
							- Swap Handler: Goal: Evict a page t disk to free frame for new page 
								- If frame modified, write into free location on swap 
								- Find pages in any address space that map to frame being evicted
									- Map from frame to page
									- Change corresponding PTE to invalid
									- Set remaining bits in PTE to point to location on swap 
								- Return newly freed frame 

Managing Swap 
	- Dirty pages place on swap? 
		- Use a bitmap or linked list of swap frames (technique similar to managing memory) 
		- Swap frames do not need to be contiguous on disk but is better if they were. 
	- Evicting page to swap 
		- find a free swap frame
		Write page to this location on disk 
		- Can use invalid Page Table Entry to note location of swap frame 
		- on page fault, use PTE to locate where swap frame are. 
		
			
Copy on write
	- Invalidate TLB Entry 

Fork() with copy on write
	- FLush TLB Entry 
	
File read system call does not affect page table element
	- Make no changes to TLB entry 
			
Context Swtich
	- FLush TLB Entry 
	
Page Eviction
	- Invalidate TLB entry 

CPU Interrupt	
	- Make no changes to TLB entry
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Disk
-----------------------------------------------------------------------------------------------------------------------------------------------------

	
Shortest Seek First 
	- Minimizes arm motion 
	- Disadvantage: Starvation is possible
	- Tend to favor middle tracks 
	- Note: Little benefit if very few request in scheduler queue at a time. 

File block placement 
	- Files are placed close to each other in a cylinder to reduce seek time. 
	
Seek time calculation: 

Time to read one data block = seek time + transfer time + rotation time 

Transfer time if XB per second, and one data block is 4KB 
basically just divide 4KB/XB = time to transfer 1 data block  (convert to millisecond by multiplying with 1000) 
Random rotation => time to get 1/2 rotation 
Y RPM = Y/60 RPS 

X rotations per minute / 60   = Z rotations per second => 1 rotation is 1/Z seconds
=> transfer time for 1 track is 1/Z seconds 
If 1 track has 50 blocks
=> Transfer time for 1 block is (1/Z) / 50

88% hit rate => 
0.88 * (transfer time only since from cache) + 0.12 * (seektime + transfer time + rotation time from disk) 


If increase disk block cache results in slower applications, its because: 
1. Reduces amount of memory that can be allocated to the page cache since disk block cache used up most of main memory  
=> i) applications that have very large code segments 
   ii) applications that have large data segments (e.g. large array) 
   results in lots of page eviction 
Redundant Array of Inexpensive Disk (RAID) 
RAID 0 = Disk striping => One disk for each , distribute data across several disk for speed 
			=> Can read each disk simultaneously 
Raid 1 => Mirror everything => twice disk needed (backup solution)
Raid 4 => 1 parity disk so can xor (minimize number of disk) 
Raid 5 => Allocate parity bit randomly so can reduce bottleneck on parity disk itself 
Raid 6 -> Can recover from  loss of 2 disk 
   
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Files
-----------------------------------------------------------------------------------------------------------------------------------------------------

Files = Abstraction for disk 
Each thread thinks it has its own disk by accessing files 
Don't need know actual location of blocks of a file 


FIles from 1 file system cannot have a hard link to file on another file systems since the inode number 
may represent different things regardless of whether it 2nd system is mounted within the first system. 

File System Design 

OS needs to  store and retrieve files and directories 
=> OS needs to maintain information on where they are stored. 

Data should still exist when machine reboots: 
i) Crash
ii) Restart 
Data still needs to exist 

Disk blocks 
- Granularity of sectors (512bytes) 
- is an array of blocks
- Each block  has 2^n contiguous sectors 
- n increase -> Better throughput but larger internal fragmentation

File system has 4 main tasks
1. Free block management 
	- Allocates blcoks to a file, manages free blocks
	- Use bitmaps, linkedlist , b trees 
	- Similar to memory and swap management (Block on Demand) 

2. Block allocation and placement 
	- maps non-contiguous blocks to file (using Inode Table) 
	- Issues similar to virtual memory , placement is unique to file system. 
	
3. Directory management 
	- Maps file names to location of starting block of file 

4. Buffer cache managment
	- caches disk blocks in memory to minimize IO 
	
	
Task 1: 
Free Block Management 
	- Bitmaps -> Stored in separate area on disk 
		- 1 if memory is being used (valid) , 0 if it is invalid 
	- 1 bit per disk block 
	- Block size = 1KByte, Disk Size = 16GByte
	- Number of blocks = DIskSize/BlockSize = 16M
	- 1 block can store 1KB => 1000Byte = 8000bits => 8000 entries since 1 entry is 1 bit 
	Number of bitmap blocks = NumberOfBlocks/NumberofBitmapsPerBlock = 16M/8 (to convert to bytes) = 2MByte 

Task 2:	
Block Allocation 
	- Map non contiguous blocks to a file 
		i) Contiguous Allocation
			- All blocks in file are contiguous on disk 
				=> Performance is good for sequential reading
				=> File growth requires copying
				=> Disk becomes fragmented after deletion 
				=> Will need periodic compaction ( Want to shrink the space )
			- Used in CD ROM 
				Since all file sizes are known in advance
				Files are never deleted
		ii) Linked List allocation 
			- Each file is a linked list of blocks 
			- First word in a block contains number of next block 
			- Random access is slow! => Looking at first word in that node and traverse every node to get to node you want  
			
		iii) File Allocation Table (FAT) 
			- Keep linked list information in meory 
			- Uses an index table with one entry per disk block 
				- Each entry contains address of next block 
			- Advantages => Random accesss needs in memory serach (fast) 
			Similar to linked list but search is faster since no memory access 
			Disadvantage => Entire table stoed in memory, doesn't scale with large file systems 
		Recap: 
		Linked list allocation spreads index information on isk 
			- slow random acess
		FAT keeps linked list index information in memory 
			-Limits size of file system. 	
			
	- Inode Based Allocation  (Inode => A pointer to something you want _ d
		Store index information for locating file blocks close together on disk 
		Cache this info in memroy when file is open 
		These avoids slow random access as well as limited file system. 
		Dynamic memory allocation to increase index information  will not allowe contiguous memory allocation. 
		- Use a tree to store index information 
			- Tree allows grwoth of index information 
				- Twelve direct blocks points to file data blocks 
				- 13th (1) indirect pointer points to an indirect block
					indirect block is a block of pointers that point to direct blocks 
						number of pointers = sizeOfDataBlock/sizeOfPointers
				- 14th (1) double indirect pointer that points to a double indirect block 
					double indirect block is a block of pointers that point to indirect blocks
				- 15th (1) triple indirect  pointer that points to a triple indirect block
					triple indirect block is a block of pointers that points to double indirect blocks 
	- Block Placement
		- Block placement is the policy used by filesystem for block allocation 
			- Disk layout of UNIX File system. 

Pointer to data block is stored in (single indirect block or Inode) 
Access control info. is stored in (inode) 
Hard Link name is stored in (data block, or directory entry) 
Symbolic Link name is stored in (data block) 
Directory name is stored in (directory entry, or data block) 
Executable header is stored in (data block) 
Pointer to double indirect block ( inode, triple indirect block 
Inode number is stored in (Director entry or data block) 





			
Fast File System => The way you put files on disk 
	- Each cylinder group (same tracks across platter) 
		- Inode and data blocks of a file 
		- Files in a directory 
		- Cylinder group is full => Place in nearby group 
		
Task 3: 
Directory Management 
	- A directory contains 0 or more entries
		- 1 entry per (file or subdirectory) in that directory 
		- Entries are kept in directory data blocks 
	- Each entry maps file name to location of starting block has
		- File name, file attributes, Block number of first block of file. 
		
		filename, attirbutes, blockNumber
		
	- In UNIX , 
		each entry has: filename, InodeNumber 
			Inode contains file attributes 
			Hard Links => MOre than 1 name for a file, 
				Different directory entries can have the same inodenumber
				The inode for that file maintains reference count 
				Directed Acyclic Graph only if not deletion of directories is difficult (need cycle detection algorithm) 
			File Deletion 
				- Directory entry is removed from directory 
				- All blocks in file are returned to free list 
				- Hard Links
					- Put a refence count field in each inode
					- Count number of entires that point to the file
					- When removing file, decrementr count
					- When count goes to 0, reclaim all file blocks
				- Symbolic Link 
					(Points to bad data if file was deleted) 

Task 4:					
Buffer Cache Management  = Block Cache Management
	- File operations often access the same disk block 
	- Caching disk blocks in memory reduces disk I/O
	- Block cache = buffer cache
	- Block Lookup() => If block in memory returns data from buffer
	- Block Miss() => Read disk block into buffer, update buffer cache
	- Block flush() => If buffer modified, write back to disk blocks 
	
	Look up blocks more efficiently using hash table
		key is (device, block #) 
		value is a block in memory 
	
	Buffer Cache Write Policy 
		- WHen block needs to be written, buffer in buffer cache is updated
			Updated immediately(Write through0
			Updated later (Write-back cache) 
				- But if system crashes? 
					- Use journaling system = write ahead logging 
					
	Read Ahead -> Prefetch nexgt block from disk 
	
Sharing Files = Files shared accross processes
i) Concurrent access
	Sequential concurrency 
		- read() sees data from most recent finished write() system call.
		- All processsors see same order of writes
			- If file's value was changed from 1 to 2 , processor will never read 2 then 1. 
			- However, it may read 1 or it may read 2 
ii) Protection (only authorized user access files) 	
		- Access Control List (Each object has a liswt of subjects and permissions) 
			- Easy to manage and implement
			- Problem if a lot of subjects
				- solve using groups
		- Capabilities 
			- For each subject, maintain list of objects and permitted action
				- easy to transfer (like keys) 
				- Problem to revoke capability since need keep track of all subjects that have capability 
		
Proces -> Open File Table 	-> 		Inode 	-> Disk Blocks 
// IN Memory 						// IN Disk
open(name, mode) 
	- traverse directory tree
	- find and cahce inode for file in buffer cache
	- check permissions
	- set up entry in open file table 
	- set up entry in file descriptor table
	- return fd

byte_count = read(fd, buffer, buffer_size)
	- figure out data and indirect blcoks to read
	- read from disk into buffer cache
	- copy data to user buffer
	- update file position
	- return number of bytes read
	
byte_write = write(fd, buffer, numBytes)
	- figoure out data and indirect blocks to write
	- read from disk into buffer cache
	- copy dat from user buffer into bocks in buffer cache
	- update file position
	- update inode
	- mark modified buffers (mark as dirty) 
	- return number of bytes written
	
close(fd)
	- reclaim resources
	

Consistency and Crash Recovery 
	- write back may cause inconsistency during crash since dirty blocks in memory are lost
	- 
	
	Journaling 
		- Advantage: Speed up crash recovery
		- Disadvantage: Every write becomes 2 writes instead. 
		
		
Original UNIX File System problem (THE ONE THAT USES 15 , 12 DIRECT, ETC.) 
	1. Aging (More random file allocation) 
	2. Inode far From Data blocks (lots of long seeks between inode and data blocks when traversing between directories) 

max file size = pointer size * block size 
	
-----------------------------------------------------------------------------------------------------------------------------------------------------
// Extra	
-----------------------------------------------------------------------------------------------------------------------------------------------------
Similarities between web browsers and operating systems? 
1. Both run multiple applications
2. Both need to isolate and protect different application
3. Ensure own code is safe from application code

Diffences between web browsers and operating systems? 
1. OS uses hardware protection, browsers uses software protection for security 
2. OS has direct access to hardware whereas browser must use OS to access hardware 
3. OS run local code whereas web browser runs remote code and displays remote data. "

Thrashing 
1. All threads keep replacing each other's pages and no actual work gets done

Need Hardware Support
1. System Call for Mode Switch
2. Context Swtich for update Address Register(MMU Register) 
3. Acquiring a lock for Disable interrupts

Checks to argument
1. It exists 
2. It lies within user space
3. It terminates (has '\0' for strings) 

Executing privileged instruction from user-level process causes 
trap (exception) to OS. 

Extent => Very expensive to resize  (disadvantage) , also large external fragmentation if large contiguous memory (disadvantage) 
Extent => Fast access (advantage) , only 1

No Preemptive benefits
	- More efficient since less context switch
	- Code easier to implement
	
Preemptive benefits
	- Helps prevent starvation since Context Switch occurs
	- More interactive system 

Feedback based scheduling can help avoid starvation because it prioritizes IO bound processes over CPU bound processes. 
IO bound would not starve CPU as if it uses CPU excessively, its priority value will increase and priority will reduce to below CPU bound process
Therefore, it prevents starvation 

