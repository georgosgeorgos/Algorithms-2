//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Coordinate Format Sparse Matrix (COO in scipy), T(n, m, k) = O(k), S(n, m, k) = O(3k)
2. Compressed Sparse Row Matrix (CSR in scipy), T(n, m, k) = O(k), S(n, m, k) = O(2k + (n+1))
3. Compressed Sparse Column Matrix (CSC in scipy), T(n, m, k) = O(k), S(n, m, k) = O(2k + (m+1))
//-------------------------
TODO:
Implement all the Scipy sparse matrix implementations
Block Compressed Sparse Row (BSR in scipy) => CSR on Blocks
Block Compressed Sparse Column  => CSC on Blocks
Diagonal Storage (DIA in scipy) => Diagonal Storage
Dictionary of Keys (DOK in scipy) (similar to COO, but hashes[(userIndex, itemIndex)] -> Value)
List of List Row (LIL in scipy) => Each row is index to array, each value of array is a linked list of non-zero column with values
List of List Column => Each col is index to array of items, each value is a linked list of non-zero rows with values
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Coordinate Format Sparse Matrix (COO in scipy)
// Time Complexity, T(n, m, k) = O(k)
// Space Complexity, S(n, m, k) =  O(3k)
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

class SparseMatrixCoordinate { public:
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
// 2 Compressed Sparse Row Matrix (CSR in scipy)
// Time Complexity, T(n, m, k) =  = O(k)
// Space Complexity, S(n, m, k) =  O(2k + (n+1))
//---------------------------------
/*
Let
n = numRow
m = numCol
k = number of non-zero elements
Storage => O(2k + (n+1)) = O(k + n)
*/
//---------------------------------
/* //
#include <vector>
#include <iostream>
using namespace std;

class SparseMatrixCompressedSparseRow {
public:
    SparseMatrixCompressedSparseRow(vector<vector<int>>& matrix);
    ~SparseMatrixCompressedSparseRow();
    vector<int> dotProductVector(const vector<int>& vec);
private:
    vector<int> row;
    vector<int> col;
    vector<int> val;
};

SparseMatrixCompressedSparseRow::SparseMatrixCompressedSparseRow(vector<vector<int>>& matrix) 
{
    int numNotZero = 0;
    for (int rowIndex = 0; rowIndex < matrix.size(); rowIndex++)
    {
        this->row.push_back(numNotZero);
        for (int colIndex = 0; colIndex < matrix[rowIndex].size(); colIndex++)
        {
            int currVal = matrix[rowIndex][colIndex];
            if (currVal != 0)
            {
                this->col.push_back(colIndex);
                this->val.push_back(currVal);
                numNotZero++;
            }
        }
    }
    this->row.push_back(numNotZero);
}

SparseMatrixCompressedSparseRow::~SparseMatrixCompressedSparseRow() {}

vector<int> SparseMatrixCompressedSparseRow::dotProductVector(const vector<int>& vec)
{
    vector<int> result(vec.size(), 0);
    for (int rowIndex = 0; rowIndex < this->row.size() - 1; rowIndex++)
    { 
        for (int index = this->row[rowIndex]; index < this->row[rowIndex + 1]; index++)
        {
            result[rowIndex] += vec[this->col[index]] * this->val[index];
        }
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
    SparseMatrixCompressedSparseRow smcsr(sparseMatrix);
    vector<int> vec = {1, 1, 1, 1, 1};
    vector<int> result = smcsr.dotProductVector(vec);
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
// 3 Compressed Sparse Column Matrix (CSC in scipy)
// Time Complexity, T(n, m, k) =  = O(k)
// Space Complexity, S(n, m, k) =  O(2k + (m+1))
//---------------------------------
/*
Let
n = numRow
m = numCol
k = number of non-zero elements
Storage => O(2k + (m+1)) = O(k + m)
*/
//---------------------------------
/* //
#include <vector>
#include <iostream>
using namespace std;

class SparseMatrixCompressedSparseColumn {
public:
    SparseMatrixCompressedSparseColumn(vector<vector<int>>& matrix);
    ~SparseMatrixCompressedSparseColumn();
    vector<int> dotProductVector(const vector<int>& vec);
private:
    vector<int> row;
    vector<int> col;
    vector<int> val;
};

SparseMatrixCompressedSparseColumn::SparseMatrixCompressedSparseColumn(vector<vector<int>>& matrix) 
{
    // Assume its a rectangular matrix of (numRow x numCol)
    int numNotZero = 0;
    for (int colIndex = 0; colIndex < matrix[0].size(); colIndex++)
    {
        this->col.push_back(numNotZero);
        for (int rowIndex = 0; rowIndex < matrix.size(); rowIndex++)
        {
            int currVal = matrix[rowIndex][colIndex];
            if (currVal != 0)
            {
                this->row.push_back(rowIndex);
                this->val.push_back(currVal);
                numNotZero++;
            }
        }
    }
    this->col.push_back(numNotZero);
}

SparseMatrixCompressedSparseColumn::~SparseMatrixCompressedSparseColumn() {}

vector<int> SparseMatrixCompressedSparseColumn::dotProductVector(const vector<int>& vec)
{
    vector<int> result(vec.size(), 0);
    for (int colIndex = 0; colIndex < this->col.size() - 1; colIndex++)
    { 
        for (int index = this->col[colIndex]; index < this->col[colIndex + 1]; index++)
        {
            result[this->row[index]] += vec[colIndex] * this->val[index];
        }
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
    SparseMatrixCompressedSparseColumn smcsc(sparseMatrix);
    vector<int> vec = {1, 1, 1, 1, 1};
    vector<int> result = smcsc.dotProductVector(vec);
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
