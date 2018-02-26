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
// Time Complexity, T(n, m, k) =  = O(k)
// Space Complexity, S(n, m, k) =  O(k)
//---------------------------------
/*
Let
n = numRow
m = numCol
k = number of non-zero elements
Storage => O(3k) = O(k)
*/
//---------------------------------
/* //
#include <vector>
#include <iostream>
using namespace std;

class SparseMatrixCoordinate {
public:
    SparseMatrixCoordinate(vector<vector<int>>& matrix);
    ~SparseMatrixCoordinate();
    vector<int> dotProductVector(const vector<int>& vec);
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
                this->row.push_back(rowIndex);
                this->col.push_back(colIndex);
                this->val.push_back(currVal);
            }
        }
    }
}

SparseMatrixCoordinate::~SparseMatrixCoordinate() {}

vector<int> SparseMatrixCoordinate::dotProductVector(const vector<int>& vec)
{
    vector<int> result(vec.size(), 0);
    for (int index = 0; index < this->row.size(); index++)
    {
        result[this->row[index]] += vec[this->col[index]] * this->val[index];
    }
    return result;
}

int main(void)
{
    int N = 5;
    vector<vector<int>> sparseMatrix(N, vector<int>(N, 0));
    sparseMatrix[0][1] = 2;
    sparseMatrix[0][4] = 3;
    sparseMatrix[1][3] = 7;
    sparseMatrix[2][1] = 8;
    sparseMatrix[3][3] = 9;
    sparseMatrix[4][0] = 5;
    sparseMatrix[4][3] = 1;
    SparseMatrixCoordinate smc(sparseMatrix);
    vector<int> vec = {1, 1, 1, 1, 1};
    vector<int> result = smc.dotProductVector(vec);
    // Output: [5, 7, 8, 9, 6]
    cout << "[";
    for (int val : result)
    {
        cout << val << ", ";
    }
    cout << "]" << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
