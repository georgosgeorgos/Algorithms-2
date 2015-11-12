//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Rotate 2D Image (N x N) 90 Degrees In Place, T(n) = O(n^2), S(n) = O(1)
2. Traverse (NxM) array spirally, T(n,m) = O(nm), S(n,m) = O(nm), (Bloomberg Interview)
3. Given a N x M matrix of integers, if an element is 0, its entire row and column are set to 0, T(n,m) = O(nm), S(n,m) = O(n + m)
//-------------------------------------------
TODO:
Find maximum sum rectangle 
//-------------------------------------------
// Notes
vector< vector<int> > arr(N, vector<int> (M, 0)); // initialize arr[N][M] with all elements equal 0
// */
//----------------------------------------------------------------------------------------
// 1 Rotate 2D Image (N x N) 90 Degrees In Place
// Rotate an image 90 degrees in place. Can create constant memory but not an entire array
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(1)
//-------------------------------------------
/* //
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

void rotate90InPlace(int** image, int n);

int main(void)
{
    int counter = 1;
    int** image;
    image = (int **) malloc(sizeof(int*) * 4);
    int i = 0;
    int j = 0;
    for (i = 0; i < 4; i ++)
    {
        image[i] = (int *) malloc(sizeof(int) * 4);
        for ( j = 0; j < 4; j++)
        {
            image[i][j] = counter;
            counter++;
        }
    }

    for (i = 0; i < 4; i ++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%d   ", image[i][j]);
        }
        printf("\n");
    }    printf("%f %f INSWAP\n", a, b);

    rotate90InPlace(image, 4);
    printf("After Rotating \n");

    for (i = 0; i < 4; i ++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%d   ", image[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// Simply perform a swap operation across 4 elements instead of the usual 2 elements
// Basically, for a given N x N matrix, 
// you will have to traverse a total of floor(N/2) layers. 
// You traverse from the outer layer to the inner layer. 
// At each layer, you need to go through 'end1' number of offsets
// i = Layer number
// j = Offset number at a given layer
// end1 = Number of offsets at a given layer 
// end2 = The inverse location of offset number for j 
// Really, you are just solving for the 4 swap operation indices
// [Row][Column]
// [j][i]
// [i][end2]
// [end2][end1]
// [end1][j]
// Take note of how the pattern changes 
void rotate90InPlace(int** image, int n)
{
    int i = 0; // i = layer #
    int j = 0; // j = offset #
    // floor(n/2) => Number of layers for a given N x N matrix
    for (i = 0; i < floor(n/2); i++)
    {
        int end1 = n - i - 1; // Number of offsets in current layer
        for(j = i; j < end1; j++)
        {

            int end2 = n - j - 1; // Inverse offset location  for current offset #, j
            int temp = image[j][i];
            image[j][i] = image[i][end2];
            image[i][end2] = image[end2][end1];
            image[end2][end1] = image[end1][j];
            image[end1][j] = temp;
        }
    }
    return;
}
// */
//----------------------------------------------------------------------------------------
// 2 Traverse (NxM) array spirally
// Time Complexity, T(n,m) = O(nm)
// Space Complexity, S(n,m) = O(nm)
//-------------------------------------------
/*
Questions:
    1. Is size of array always n^2? or O(nm)
    2. int or doubles? 
    3. Counter clockwise or clockwise? 
FunctionPrototype:
    void traverseSpiral(vector< vector<int> >& matrix);
TestCases:
    [[1,2],
     [3,4]
     ]
     => 1,2,4,3? 
Algorithm:   
    Traverse top right to btm, then call recursively 
    Recursive calls can take a maximum depth of O(nm)
*/
//-------------------------------------------
/* //
#include <vector>
#include <iostream>
using namespace std;

void printMatrix(vector< vector<int> >& matrix) 
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void traverseSpiralRightDown(vector< vector<int> >& matrix, int y, int x, int depth);
void traverseSpiralLeftUp(vector< vector<int> >& matrix, int y, int x, int depth)
{
    // base case: 
    if(x < depth || y < (depth + 1)) return;
    while(x >= depth)
    {
        cout << matrix[y][x] << " ";
        x--;
    }
    x++; // increment as decremented from exiting while loop
    y--; // skip current cell
    while(y >= (depth + 1)) // need to add 1 here
    {
        cout << matrix[y][x] << " ";
        y--; // Mistake: Decremented y before printing
    }
    y++; // increment as decremented from exiting while loop
    x++; // skip current cell
    return traverseSpiralRightDown(matrix, y, x, depth+1); // must increment depth here
}

void traverseSpiralRightDown(vector< vector<int> >& matrix, int y, int x, int depth)
{
    // base case: 
    if(x >= matrix[0].size() - depth || y >= matrix.size() - depth) return;
    while(x < matrix[0].size() - depth)
    {
        cout << matrix[y][x] << " ";
        x++;
    }
    x--; // decrement as incremented from while loop
    y++; // skip current cell
    while(y < matrix.size() - depth)
    {
        cout << matrix[y][x] << " ";
        y++; // Mistake: Incremented y before printing
    }
    y--; // decrement as incremented from whle loop
    x--; // skip current cell
    return traverseSpiralLeftUp(matrix, y, x, depth); // don't increment depth here
}

void traverseSpiral(vector< vector<int> >& matrix)
{
    if(matrix.size() <= 0 || matrix[0].size() <= 0) return;
    traverseSpiralRightDown(matrix, 0, 0, 0);
    cout << endl;
}

int main(void)
{
    int N = 3, M = 3;
    vector< vector<int> > matrix (N, vector<int>(M,0));
    int count = 0;
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = count;
            count++;
        }
    }
    printMatrix(matrix);
    traverseSpiral(matrix);
    N = 2, M = 5;
    vector< vector<int> > matrix2 (N, vector<int>(M,0));
    count = 0;
    for(int i = 0; i < matrix2.size(); i++)
    {
        for(int j = 0; j < matrix2[i].size(); j++)
        {
            matrix2[i][j] = count;
            count++;
        }
    }
    printMatrix(matrix2);
    traverseSpiral(matrix2);
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 3 Given a N x M matrix of integers, if an element is 0, its entire row and column are set to 0
// Time Complexity, T(n,m) = O(nm)
// Space Complexity, S(n,m) = O(n + m)
//-------------------------------------------
/* //
#include <cstdlib> 
#include <cstdio>
#include <iostream> 
#include <ctime> // for time(NULL)
using namespace std; 

void zeroOut(int** array, int n, int m); 

int main(void)
{
    srand(time(NULL));
    int N = 3;
    int M = 4; 
    // Initialize the array of size N x M as well as print the current value 
    //int a[N][M]; 
    int** a = (int**) malloc(sizeof(int*) * N);
    for(int i = 0; i < N; i++)
    {
        a[i] = (int*) malloc(sizeof(int) * M);
    }
    
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            a[i][j] = rand() % 10; // set the current cell to be a random number between [0,9]
            cout << a[i][j] << " "; 
        }
        cout << endl; 
    }
    zeroOut(a, N, M);
    // Print the final result
    cout << endl; 
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cout << a[i][j] << " "; 
        }
        cout << endl; 
    }
    return 0; 
}

void zeroOut(int** a, int n, int m) 
{
    int row[n];
    int column[m]; 
    for (int i = 0; i < n; i++)
    {
        row[i] = 0; 
    }
    for (int i = 0; i < m; i++)
    {
        column[i] = 0; 
    }

    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (a[i][j] == 0)
            {
                row[i] = 1; 
                column[j] = 1; 
            }          
        }
    }
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (row[i] || column[j])
            {
                a[i][j] = 0;
            }
        }
    }
    return; 
}
// */
//----------------------------------------------------------------------------------------
