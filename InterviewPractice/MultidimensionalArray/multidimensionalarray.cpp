//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Rotate 2D Image (N x N) 90 Degrees, T(n) = O(n^2), S(n) = O(n^2)
2. Rotate 2D Image (N x N) 90 Degrees In Place, T(n) = O(n^2), S(n) = O(1)
3. Traverse (NxN) array spirally
4. Given a N x M matrix of integers, if an element is 0, its entire row and column are set to 0, T(n,m) = O(nm), S(n,m) = O(n + m)
// */
//----------------------------------------------------------------------------------------
/*
// 1 Rotate 2D Image (N x N) 90 Degrees
// Rotate an image 90 degrees, allowed to create new array
// TODO: REDO THIS!!!!! TOO MUCH MISTAKES AT FIRST
// Time Complexity, T(n) = (n^2)
// Space Complexity, S(n) = (n^2)

#include <stdlib.h>
#include <stdio.h>

void rotate90(int** image, int row, int col);

int main(void)
{
    //int image[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int** image = (int**) malloc(sizeof(int*) * 3);
    int i = 0;
    int j = 0;

    for ( i =0; i < 3; i++)
    {
        image[i] = (int*) malloc(sizeof(int) * 3);
    }

    int count = 1;

    for ( i =0; i < 3; i++)
    {
        for( j = 0; j < 3; j++)
        {
            image[i][j] = count;
            count++;
        }
    }

    for ( i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }

    rotate90(image, 3, 3);
    printf("after rotating\n");

    for ( i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void rotate90(int** image, int row, int col)
{
    int copyImage[row][col];
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
            for(j = 0; j< col; j++)
            {
                copyImage[col-j-1][i] = image[i][j];
            }
    }

    for (i = 0; i < row; i++)
    {
            for(j = 0; j< col; j++)
            {
                image[i][j] = copyImage[i][j];
            }
    }
    return;
}

// */

//----------------------------------------------------------------------------------------
/* //
// 2 Rotate 2D Image (N x N) 90 Degrees In Place
// Rotate an image 90 degrees in place. Can create constant memory but not an entire array
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(1)
// TODO: Do this again, too many mistakes

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
/* //
// 3 Traverse (NxN) array spirally
// Traverse array Spirally
// Time Complexity O(n^2) , if array is size a[n][n]
// Space Complexity O(1)
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

void printValue(int a);
void traverseSpiralTopRight(int** a, int x1, int x2, int y1, int y2,void (*funcPointer)(int));
void traverseSpiralBottomLeft(int** a, int x1, int x2, int y1, int y2,void (*funcPointer)(int));
int main(void)
{
    int** a;    
    // Note: Can easily change value of N here due to great setup to see if it works for various values of N
    int N = 5;
    a = (int**) malloc(sizeof(int*) * N);
    int i = 0;
    for(i = 0; i < N; i++)
    {
        a[i] = (int *) malloc(sizeof(int) * N);
    }
    int count = 0;

    int j = 0;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            a[i][j] = count;
            count++;
        }
    }
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            cout << a[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    void (*funcPointer)(int) = &printValue;
    traverseSpiralTopRight(a,0, N-1, 0, N-1, funcPointer);
    return 0;
}


void printValue(int a)
{
    cout << a << " ";
    return;
}

void traverseSpiralTopRight(int** a, int x1, int x2, int y1, int y2,void (*funcPointer)(int) )
{
    int i = 0;
    int j = 0 ;
    double temp;
    for (i = x1; i <= x2; i++)
    {
        // Mistake, its [y][x] NOT [x][y]
        temp = a[y1][i];
        funcPointer(temp);
    }
    // Mistake: Start from y1+1, NOT y1
    for(j = y1+1; j <= y2; j++)
    {
        temp = a[j][x2];
        funcPointer(temp);
    }
    if (x2 - x1 > 0)
    {
        return traverseSpiralBottomLeft(a, x1, x2-1, y1+1, y2, funcPointer);
    }
    return;
}

void traverseSpiralBottomLeft(int** a, int x1, int x2, int y1, int y2,void (*funcPointer)(int))
{
    int i = 0;
    int j = 0 ;
    double temp;
    for (i = x2; i >= x1; i--)
    {
        temp = a[y2][i];
        funcPointer(temp);
    }
    // Mistake: Start from y2-1, NOT y2
    for(j = y2-1; j >= y1; j--)
    {
        temp = a[j][x1];
        funcPointer(temp);
    }
    if (x2 - x1 > 0)
    {
        return traverseSpiralTopRight(a, x1+1, x2, y1, y2-1, funcPointer);
    }
    return;
}
// */
//----------------------------------------------------------------------------------------
/* //
// 4 Given a N x M matrix of integers, if an element is 0, its entire row and column are set to 0
// Time Complexity, T(n,m) = O(nm)
// Space Complexity, S(n,m) = O(n + m)
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
