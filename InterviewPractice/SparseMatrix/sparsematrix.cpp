//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Coordinate Format Sparse Matrix
//-------------------------
TODO:
Compressed Sparse Row
Compressed Sparse Column
Coordinate Format
Block Sparse Row
Diagonal Storage
Dictionary of Keys
Row-based Linked List
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Coordinate Format Sparse Matrix
// Time Complexity, T(n) = TODO
// Space Complexity, S(n) = TODO
//---------------------------------
/*
Questions:
TestCase:
Algorithm:
*/
//---------------------------------
//
#include <vector>
#include <iostream>
using namespace std;

class SparseMatrixCoordinate {
public:
    SparseMatrixCoordinate(vector<vector<int>>& matrix);
    ~SparseMatrixCoordinate();
private:
    vector<int> row;
    vector<int> col;
    vector<int> val;
};

SparseMatrixCoordinate::SparseMatrixCoordinate(vector<vector<int>>& matrix) 
{
    for (int rowIndex = 0; rowIndex < matrix.size(); rowIndex++)
    {
        for (int colIndex = 0; colIndex < matrix[rowIndex].size(); colIndex++)
        {
            int currVal = matrix[rowIndex][colIndex];
            if (currVal != 0)
            {
                row.push_back(rowIndex);
                col.push_back(colIndex);
                val.push_back(currVal);
            }
        }
    }
}

SparseMatrixCoordinate::~SparseMatrixCoordinate() {}

int main(void)
{
    int N = 5;
    vector<vector<int>> sparseMatrix(N, vector<int>(N, 0));
    sparseMatrix[0][1] = 2;
    sparseMatrix[0][4] = 3;
    sparseMatrix[1][3] = 7;
    sparseMatrix[2][1] = 8;
    sparseMatrix[3][3] = 9;
    sparseMatrix[4][3] = 1;
    SparseMatrixCoordinate smc(sparseMatrix);
    cout << "done" << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
