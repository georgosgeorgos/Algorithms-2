//----------------------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
Greey Algorithms implemented in other folders:
    Djikstra Algorithm -> Graph
    Kruskal -> Disjoint Set
    Prim -> Graph
// TODO:
//----------------------------------------------------------------------------------------------------------------------------------------------
1.Job Sequencing Problem
Job Sequencing Problem 
Given an array of jobs where every job has a deadline and associated profit if the job is finished before the deadline. 
It is also given that every job takes single unit of time, 
so the minimum possible deadline for any job is 1. How to maximize total profit if only one job can be scheduled at a time.

Questions: 
    Can deadline be (-)? Are deadlines always integers? 
    I assume I start from time 0 right? 
    Can profit be (-)? is profit an integer ? 
    Does deadline start from 0 ? So first job’s deadline must be latest 1 instead of 0? 
    Are jobs already sorted by max profit or max deadline to begin with? 

Function Prototype: 
	int JobSequence(vector< vector<int> >& arr);
Test Case: 
    Input: Four Jobs with following deadlines and profits
      JobID    Deadline      Profit
        a        4            20   
        b        1            10
        c        1            40  
        d        1            30
    Output: Following is maximum profit sequence of jobs
            c, a   

Algorithms:
Let d = max. deadline integer - earliest deadline (0) = max num. of slots, n = number of elements
    1. Sort by max profit/time first. From largest to smallest, pick latest slot available. 
    T(n) = O(nlgn + nd) , S(n) = O(d) // to keep track of slots available

    2. (MaxHeap) Sort by decreasing deadline, for each instance of deadline from max. deadline, push all relevant deadlines to a max heap. 
    Pop max. value and assign to that deadline slot,
    then move to (deadline - 1), and push all instance of (deadline - 1) to max heap that exist which may be none, 
    then pop max heap (if there are elements in heap) and assign to (deadline - 1), continue doing so. 
    T(n,d) = (3nlgn + d) , nlgn -> sort, nlgn -> push heap, nlgn -> pop heap , d => iterate down deadline. S(n,d) = O(n)  
    (only need store heap, dont need store deadline slots since iterating downwards. 

    3. (Disjoint Set) Union-Find, initialize (d+1) disjoint sets (including slot 0 which is a base case) 
    Each disjoint set points to next available deadline same or earlier than that slot. which means each set element first points to itself as next available deadline slot. 
    Sort based on maximum value decreasing. Always pick max. value available, and if next available deadline slot for that element's deadline is > 0,
    then add it to final and join that deadline's slot with the (deadline-1)'s slot, 
    it will then point its next available slot to what the (deadline - 1)'s next available slot is. 
    T(n,d) = O(nlgn + n), S(n,d) = O(d) 
    nlgn -> sort, n to iterate through all elements, (note: no d time to find next available slot since disjoint sets are O(1)) 
    d -> Need only store each time slot as a disjoint set. 
//--------------------------------------------
// notes
// 1. For each variable type, try:
//      - Sort on that variable
//      - Continuously pick the max/min of that variable
//      - Assign it to the max and min position of something
//      - Use min/max heap to keep pulling out min/max
//      - Use disjoint set to link each element to next best element available
//
//--------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------------
