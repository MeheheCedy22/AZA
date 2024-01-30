//not done
// hungarian algorithm / dynamic programming

/*
Assignment:

3. Suppose we assign n persons to n jobs. Let C-ij be the cost of assigning 
   the i-th person to the j-th job.
    a. Use a greedy approach to write an algorithm that finds an assignment that 
       minimizes the total cost of assigning all n persons to all n jobs. Analyze your 
       algorithm and show the results using order notation.
    b. Use the dynamic programming approach to write an algorithm for the same 
       problem. Analyze your algorithm and show the results using order notation.

    J1  J2  J3
P1  10  5   5
P2  2   4   10
P3  5   1   7

Show the optimal assignment on the screen.

*/


#include <iostream>
#include <vector>

using std::cout;
using std::vector;
using std::pair;

void printMatrix(const vector<vector<int>>& matrix)
{
    for (const auto& row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int findMinInRow(const vector<vector<int>>& matrix, int row)
{
    unsigned int minVal = 0xffffffff;

    for (int j = 0; j < matrix.size(); ++j)
    {
        if (matrix[row][j] < minVal)
        {
            minVal = matrix[row][j];
        }
    }

    return minVal;
}

int findMinInCol(const vector<vector<int>>& matrix, int col)
{
    unsigned int minVal = 0xffffffff;

    for (int i = 0; i < matrix.size(); ++i)
    {
        if (matrix[i][col] < minVal)
        {
            minVal = matrix[i][col];
        }
    }

    return minVal;
}

void subtractMinInRow(vector<vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        int minVal = findMinInRow(matrix, i);
        for (int j = 0; j < matrix.size(); ++j)
        {
            matrix[i][j] -= minVal;
        }
    }
}

void subtractMinInCol(vector<vector<int>>& matrix)
{
    for (int j = 0; j < matrix.size(); ++j)
    {
        int minVal = findMinInCol(matrix, j);
        for (int i = 0; i < matrix.size(); ++i)
        {
            matrix[i][j] -= minVal;
        }
    }
}

// cover zeros with minimum number of horizontal and/or vertical lines but not diagonal
void coverZerosMinimalLines(vector<vector<int>>& matrix, vector<pair<int, int>>& lines)
{
    
 
}



vector<pair<int, int>> hungarianAlgorithm(vector<vector<int>>& matrix)
{
    cout << "Initial matrix:\n";
    printMatrix(matrix);
    cout << "\n";

    // Step 1: Subtract the minimum value in each row
    subtractMinInRow(matrix);

    cout << "Subtracted min in row:\n";
    printMatrix(matrix);
    cout << "\n";

    // Step 2: Subtract the minimum value in each column
    subtractMinInCol(matrix);

    cout << "Subtracted min in col:\n";
    printMatrix(matrix);
    cout << "\n";

    // Step 3: Cover all zeros with minimum number of lines
    vector<pair<int, int>> lines;
    coverZerosMinimalLines(matrix, lines);

    // Step 4: 

    //Cover all columns containing a (starred) zero.
    

    // Step 5:




    // teemporary return
    return vector<pair<int, int>>();
}

int main()
{
    vector<vector<int>> costMatrix = {
        {10, 5, 5},
        {2, 4, 10},
        {5, 1, 7}
    };

    /*testing*/
    // vector<vector<int>> costMatrix = {
    //     {40, 60, 15},
    //     {25, 30, 45},
    //     {55, 30, 25}
    // };
    /*---------*/
    // vector<vector<int>> costMatrix = {
    //     {30, 25, 10},
    //     {15, 10, 20},
    //     {25, 20, 15}
    // };
    /*---------*/

    vector<pair<int, int>> optimalAssignment = hungarianAlgorithm(costMatrix);

    cout << "Optimal Assignment:\n";
    for (const auto& assignment : optimalAssignment)
    {
        cout << "Person " << assignment.first + 1 << " -> Job " << assignment.second + 1 << "\n";
    }

    return 0;
}