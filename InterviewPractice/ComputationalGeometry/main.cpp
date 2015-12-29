//----------------------------------------------------------------------------------------
/*  //
Table of Contents
1. N integers, a1,...,aN, all > 0,  n vertical lines are drawn such that the two endpoints of line i is at (i, ai),(i, 0). 
   Find two lines, which together with x-axis forms a container, such that the container contains the most water.
2. 
//-------------------------
TODO: Any INTERVAL related code, since interval is essentially comparing any intersection on a single axis, intersection of lines (start point, end point)
      Computational Geometry mix sense

TODO: Collision Detection of 2 rectangles

TODO: Compute area of a polygon of size N. Hint: Triangulate the polygon 

TODO: Given N points, find the closest pair of 2 points. Solve in O(nlgn) 

TODO:

// */
//----------------------------------------------------------------------------------------
// 1 N integers, a1,...,aN, all > 0,  n vertical lines are drawn such that the two endpoints of line i is at (i, ai),(i, 0). 
// Find two lines, which together with x-axis forms a container, such that the container contains the most water.
// It can be any 2 lines, does not need to be adjacent
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
/* //
int maxArea(vector<int>& height) {
    int end = height.size() - 1; 
    int begin = 0; 
    int maxArea = 0; 
    while(begin < end)
    {
        int area = (end-begin) * min(height[begin], height[end]); 
        if (maxArea < area) maxArea = area; 
        if(height[begin] < height[end])
        {
            begin++; 
        }
        else if (height[begin] > height[end])
        {
            end--; 
        }
        else
        {
            // Cause even if taller lines inside, doesn't matter, will still be limited by height of these, so will never be more unless both are taller
            // so just move inwards for both
            begin++; 
            end--; 
        }
    }
    return maxArea; 
}
// */
//----------------------------------------------------------------------------------------
