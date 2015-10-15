//----------------------------------------------------------------------------------------------------------------------------------
/*
1. Given a set of distinct integers, nums, return all possible subsets, T(n) = O(2^n), S(n) = O(n)
//---------------------------------
TODO: 
*/
//----------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
    return 0
}
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Given a set of distinct integers, nums, return all possible subsets.
// Time Complexity, T(n) = O(2^n) as need to visit all possible subsets
// Space Complexity, S(n) = O(n) as push and pop each number
//----------------------------------------------------------------------------------------------------------------------------------
/* 
void subsetHelper(vector<int>&nums, vector<vector<int>>& solution, vector<int>& currSubset, int index)
{
    // Add to solution when meet condition
    // in this case, add to solution at each node of DFS 
    solution.push_back(currSubset); // note: also handles base case of pushing empty set
    
    // sort the nums array first 
    sort(nums.begin(), nums.end()); 
    
    // Special DFS that iteratives over everything (many starting points for DFS) 
    // as well as recursively dfs to adjacent nodes
    // in this case, the adjacent nodes are always to the right of the array. 
    for(int i = index; i < nums.size(); i++)
    {
        currSubset.push_back(nums[i]); 
        subsetHelper(nums, solution, currSubset, i+1); 
        currSubset.pop_back(); 
    }
    return; 
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> solution; 
    vector<int> currSubset; 
    // start with index of 0 
    subsetHelper(nums, solution, currSubset, 0); 
    return solution; 
}
// */
