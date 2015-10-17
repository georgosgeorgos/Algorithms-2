//----------------------------------------------------------------------------------------------------------------------------------
/*
Table of Contents
1. Given a set of distinct integers, nums, return all possible subsets, T(n) = O(2^n), S(n) = O(n) 
2. Permutation: Generate all permutation for n distinct integers, T(n) = O(n!), S(n) = O(n!) 
3. N-Queens: Given a N*N board, how many configurations for N queens such that no Queen can attack each other, T(n) = O(n!), S(n) = O(n)
4. Knight's Tour: N*M board, touch each cell exactly once, false if impossible, T(n,m) = O(8^(nm)), S(n,m) = O(nm)
5. M-Coloring : Given an undirected graph, check if every node can be colored from M colors such that no 2 adjacent have same colors, T(V,E,M) = O(M^(V+E)), S(V,E,M) = O(V+E)
//---------------------------------
TODO: 
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
// 1 Given a set of distinct integers, nums, return all possible subsets.
// Time Complexity, T(n) = O(2^n) as need to visit all possible subsets
// Space Complexity, S(n) = O(n) as push and pop each number
//---------------------------------
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
// 3 N-Queens: Given a N*N board, how many configurations for N queens such that no Queen can attack each other
// Time Complexity, T(n) = O(n!)
// Space Complexity, S(n) = O(n)
//---------------------------------
/*
Questions: 
    1. The board is represented as vector< vector<int> > ? 
    2.  Print one solution or all solution? 
    3. Return true if any configuration or all configurations? 
Function Prototype: 
    int nQueens(int N);
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
    Chances of backtrack is when queens collide, for 2 rows, the chances are slim, but at the last row chances are high, 
    so going to be close to n*(n-1)*...*1 = n!
Implement!
*/
//---------------------------------
/* //
#include <cmath> // abs()
#include <vector>
#include <iostream> 
using namespace std; 

bool isSafe(int index, int col, vector<int>& state)
{
    // Check vertical, horizontal and diagonal with previous
    for(int i = 0; i < index; i++)
    {
        // note: Will never be in same row based on how solution is constructed
        // Check if assigned same row or diagonal with a previous queen
        if(state[i] == col || (abs(i-index) == abs(state[i]-col)))
            return false;
    } 
    return true;
}

void searchSolutions(int N, int& numConfigurations,vector<int>& state, int index)
{
    // Step 1: Goal Test: All Queens assigned legally
    if(index == N) numConfigurations++;

    // Step 2: Loop through each possible column for current row
    for(int i = 0; i < N; i++) 
    {
        // Step 3: Check Legal Moves
        if(isSafe(index, i, state))
        {
            // Step 4: Assign Move
            state[index] = i; 
            // Step 5: Search for solution
            searchSolutions(N, numConfigurations, state, index + 1);
            // Step 6: Backtrack
            state[index] = -1; 
        }
    }
    return;
}

int nQueens(int N)
{
    // Keep track of total number of configurations
    int numConfigurations = 0;
    // To store that state of each queen
    vector<int> state (N, -1); // initialize all queens to not be assigned to any position. 
    searchSolutions(N, numConfigurations,state, 0);
    return numConfigurations; 
}

int main(void)
{
    int N = 8; 
    int result = nQueens(N); // 92
    cout << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 4 Knight's Tour: N*M board, touch each cell exactly once, false if impossible
// Time Complexity, T(n,m) = O(8^(nm))
// Space Complexity, S(n,m) = O(nm)
//---------------------------------
/*
Questions: 
    1. Do I print one solution or all solution? (first solution found is enough, there's too many possible solutions)
Function Prototype: 
    
TestCase:
Algorithm: 
    Backtracking 
    Time Complexity = 8^(nm-1), (-1 because first move will never be backtracked
                The total number of orders are 8*8*8... for nm times. 
Implement!
*/
//---------------------------------
/* //
#include <vector>
#include <iostream> 
using namespace std; 

bool isSafe(int x, int y, vector< vector<int> >& matrix, int move, int N, int M, vector<int>& xAdd, vector<int>& yAdd)
{
    // Check for out of bounds or explored cells
    if ( ((x + xAdd[move]) < 0) || ((x+xAdd[move]) >= N) || ((y + yAdd[move]) < 0) || ((y + yAdd[move]) >= M) || (matrix[x + xAdd[move]][y + yAdd[move]] != -1))
        return false;
    return true;
}

bool backtrack(int N, int M, vector< vector<int> >& matrix, int index, int x, int y, vector<int>& xAdd, vector<int>& yAdd)
{
    // Step 1: Goal Test: All cells filled when current step is legal and it is 1 more than total space available on board
    if (index == N*M) return true;

    // Step 2: Iterate through possible moves
    for(int i = 0; i < 8; i++)
    {
        // Step 3: Check if current move assignment is safe
        if(isSafe(x, y, matrix, i, N, M, xAdd, yAdd))
        {
            // Step 5: Assign Legal Move
            x += xAdd[i]; y += yAdd[i];
            matrix[x][y] = index;
            if(backtrack(N, M, matrix, index + 1, x, y, xAdd, yAdd))
                return true; // return first solution found
            // Step 6: Backtrack
            matrix[x][y] = -1;
            x -= xAdd[i]; y -= yAdd[i];
        }
    }
    return false;
}

vector< vector<int> > knightTour(int N, int M)
{
    // Let -1 represented unrepresented cell
    vector< vector<int> > matrix(N, vector<int> (M, -1));
    // Initialize all possible moves 
    vector<int> xAdd = {2,1,-2,1,-1,2,-1,-2};
    vector<int> yAdd = {1,2,1,-2,2,-1,-2,-1};
    // Try every possible starting point until a solution is found
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            matrix[i][j] = 0; 
            if (backtrack(N,M,matrix,1,i,j, xAdd, yAdd)) // MISTAKE: Passed in wrong values as step = i, x = j, y = 1 instead so failed!
                    return matrix;
            matrix[i][j] = -1; // backtrack
        }
    }
    return matrix;
}

int main(void)
{
    int N = 5; 
    int M = 5; 
    vector< vector<int> > arr = knightTour(N,M); // Should terminate with solution immediately for  (5*5)
    for(int i = 0; i < arr.size(); i++)
    {
        for(int j = 0; j < arr[i].size(); j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 5 M-Coloring : Given an undirected graph, check if every node can be colored from M colors such that no 2 adjacent have same colors
// Time Complexity, T(V,E,M) = O(M^(V+E)) (note: Not sure if this is right but it is definitely exponential)
// Space Complexity, S(V,E,M) = O(V+E)
//---------------------------------
/*
Question:
    1. Must I use all colors in my graph?
TestCase: 
    a---b
    |   |
    c---d
    =>  M = 2 => True
Algorithm:
    note; if M == k is true, then M = k + i must be true since doesn't have to use all colors, i >= 0
    Since need to check for every adjacent node (edge) instead of whether 2 nodes have an edge, 
    Adjacency List will be a better representation than Adjacency Matrix
*/
//---------------------------------
/* //
#include <vector> // for colors
#include <list>
#include <iostream> 
using namespace std; 

class Graph {
private:
    list<int>* adj; // a pointer to a list of integers
    int numNodes;
    vector<int> colors; 
    bool isSafe(int index, int color) // MISTAKE: Named local variable to be same as member variable 'colors'
    {
        // Check each adjacent node to current vertex index isn't the same color
        for(auto i = adj[index].begin(); i != adj[index].end(); i++) // MISTAKE: Used 'int i' instead of 'auto i'
        {
            // check that the adjacent node hasn't been assign color or not same color by checking if it is same color
            if(this->colors[*i] == color)
                return false;
        }
        return true;
    }
    bool searchForSolution(int M, int index) // O(V)
    {
        // Step 1: Goal Test
        if(index == this->numNodes) return true; // MISTAKE: Made index==M instead of index==V
        // Step 2: Check assigning current node to each color
        for(int i = 0; i < M; i++) // O(M)
        {
            // Step 3: Check no adjacent node has this color
            if(this->isSafe(index,i)) // O(E) for isSafe and total for all checking
            {
                this->colors[index] = i; // Step 4: Assign Valid Color
                if(searchForSolution(M,index+1)) // Step 5: Serach for solution
                    return true;
                this->colors[index] = -1; // Step 6: Backtrack
            }
        }
        // Didn't find any color that fits
        return false;
    }

public:
    Graph(int V)
    {
        this->numNodes = V;
        this->adj = new list<int>[V]; 
        for(int i = 0; i < V; i++)
            this->colors.push_back(-1); // initialize all to be uncolored (-1)
    }
    void addEdge(int v, int w)
    {
        this->adj[v].push_back(w);
        this->adj[w].push_back(v); // undirected, unweighted since weight doesn't matter
    }
    bool mColoring(int M)
    {
        return this->searchForSolution(M,0);
    }
    void printColors()
    {
        for(int i = 0; i < this->numNodes; i++)
        {
            cout << colors[i] << " ";
        }
        cout << endl;
    }
};

int main(void)
{
    Graph* g = new Graph(4);
    g->addEdge(0,1);
    g->addEdge(0,2);
    g->addEdge(1,3);
    g->addEdge(2,3);
    int M = 2;
    bool result = g->mColoring(M);
    if(result) 
    {
        cout << M << " colors is possible" << endl;
        g->printColors();
    }
    else cout << M << " colors is NOT possible" << endl;
    M = 1;
    result = g->mColoring(M);
    if(result) 
    {
        cout << M << " colors is possible" << endl;
        g->printColors();
    }
    else cout << M << " colors is NOT possible" << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
