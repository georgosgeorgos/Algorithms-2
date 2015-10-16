// 
//----------------------------------------------------------------------------------------------------------------------------------
/*
Table of Contents
1. Given a set of distinct integers, nums, return all possible subsets, T(n) = O(2^n), S(n) = O(n) 
2. Permutation: Generate all permutation for n distinct integers, T(n) = O(n!), S(n) = O(n!) 
//---------------------------------
TODO: 
3. N Queen (Started below)
13. Knight's Tour
14. M Coloring
15. Subset Sum 
16. Given n distinct integers, list all k subsets that exist, k <= n, easy just, only add to solution when length of subset is k. (Similar to 1.
17. Make Valid Equation
18. Find path in N*N maze 
//---------------------------------
// Questions:
//---------------------------------
    1. Does order of output matter? 
    2. Do I print the solution or return number of solutions ?
    3. Do I need to find all solutions or just output the 1st solution found? 
//---------------------------------
// notes;
//---------------------------------
Subsets => Order/Permutation doesn't matter. 
Duplicates harder than Distinct, since Distinct is just all permutations, whereas duplicates, if need prevent duplicates, need to account for that

Every Backtracking Algorithm can be broken down into these steps: 
    Step1. Goal Test: Append to solution or return true if reach goal
    Step2. Iterate Possible Moves: Iterate through the list of possible moves
    Step3. Check Legal Move: Check if current move is legal 
    Step4. Add Move: Add new legal move
    Step5. Search Next Move: Repeat Step 1 to 5 for next move
    Step6. Backtrack: Remove move as current move doesn't work
*/
//----------------------------------------------------------------------------------------------------------------------------------
// TODO:3 N Queens: Given a N*N board, how many configurations for N queens such that no Queen can attack each other
// Time Complexity, T(n) = O()
// Space Complexity, S(n) = O(n)
//---------------------------------
/*
Questions: 
    1. The board is represented as vector< vector<int> > ? 
    2.  Print one solution or all solution? 
    3. Return true if any configuration or all configurations? 
Function Prototype: 
    int NQueens(int numQueen); 
TestCase: 
    1. N=4 => 2
    2. N=6 => 8
    3. N=8 => 92
Algorithms: 
    Each row can have N choices, there are N rows. Therefore, Brute Force takes O(n^n)
    Space can be O(n), since only store position of queen at each row which is 1 position.
    Backtrack when solution is impossible. 
    Have a row and column to mark as can't for each row and column a queen is in, however, must also mark diagonals
    Therefore, need O(n^2) space for  checking diagonals, but updating/checking diagonal takes O(n) each placement
    Better to just check if clashes at each step you put a queen down rather than mark every time you place a queen 
    as you can't guarantee that 2 queens that marked the same spot will maintain that spot if 1 queen is removed
    Step 1: If Numassign = N, append to solution 
    Step 2: Iterate through all possible columns for current row(index) 
    Spte 3: Check Safe by checking existing queens that were assigned values 
        if ( (x1 == x2) || (y1 == y2) || (abs(x1-x2) == abs(y1-y2))) return false =D came up with this yourself
        otherwise return true 
    Step 4: Assign to row and index
    Step 5: Increment row and recursively call function
    Step 6: Backtrack by un-assigning this queen
Implement!
*/
//---------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Given a set of distinct integers, nums, return all possible subsets.
// Time Complexity, T(n) = O(2^n) as need to visit all possible subsets
// Space Complexity, S(n) = O(n) as push and pop each number
//----------------------------------------------------------------------------------------------------------------------------------
/* //
#include<vector>
#include<algorithm> // sort()
#include <iostream> 
using namespace std; 

void subsetHelper(vector<int>&nums, vector<vector<int>>& solution, vector<int>& currSubset, int index)
{
    // Step1: Goal Test: add to solution at each node of DFS 
    solution.push_back(currSubset); // note: also handles base case of pushing empty set
    
    // Special DFS that iteratives over everything (many starting points for DFS) 
    // as well as recursively dfs to adjacent nodes
    // in this case, the adjacent nodes are always to the right of the array. 
    for(int i = index; i < nums.size(); i++) // Step2: Iterate Possible Moves
    {
        // Step3: Check Legal Move: It is always legal in this case
        currSubset.push_back(nums[i]);  // Step4: Add Move
        // PERMUTE TO NEXT STEP
        subsetHelper(nums, solution, currSubset, i+1); // Step5: Search Next Move 
        currSubset.pop_back(); // Step6: Backtrack
    }
    return; 
}

vector<vector<int>> subsets(vector<int>& nums) 
{
    vector<vector<int>> solution; 
    vector<int> currSubset; 
    // sort the nums array first 
    sort(nums.begin(), nums.end()); 
    // start with index of 0 
    subsetHelper(nums, solution, currSubset, 0); 
    return solution; 
}

int main(void)
{
    vector<int> arr = {1, 2, 3}; 
    vector< vector<int> > result = subsets(arr);
    for(int i = 0; i < result.size(); i++)
    {
        for(int j = 0; j < result[i].size();j++)
        {
            cout << result[i][j] << " "; 
        }
        cout << endl;
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Permutation: Generate all permutation for n distinct integers 
// Time Complexity, T(n) = O(n!)
// Space Complexity, S(n) = O(n!) 
//----------------------------------------------------------------------------------------------------------------------------------
/* // 
#include <vector>
#include <iostream> 
using namespace std; 
void swap(vector<int> & arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

void permuteHelper(vector<int>& arr, vector< vector<int> >& solution, int index)
{
    // Step1: Goal Test: Only push solution when done permuting
    if(index == arr.size()) 
        solution.push_back(arr); 

    // Step2: Iterate Possible Moves: List of possible moves are those ahead of index
    for(int j = index; j < arr.size(); j++)
    {
        // Step3: Check Legal Move: Every move is legal in this case
        swap(arr, index, j); // Step4: Add Move
        permuteHelper(arr, solution, index+1); // Step5: Search Next Move
        swap(arr, index, j); // Step6: Backtrack 
    }
    return;
}

vector< vector<int> > permute(vector<int>& arr)
{
    // Space complexity is O(n!) as need to store all n! permutations
    // This means, time complexity is at least O(n!) as well as need to visit all permutations
    vector < vector<int> > solution;
    permuteHelper(arr, solution, 0);
    return solution;
}

int main(void)
{
    vector <int> arr = {1,2,3};
    vector< vector<int> > solution = permute(arr);
    for(int i = 0; i < solution.size(); i++)
    {
        for(int j = 0; j < solution[i].size();j++)
        {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
