// done
// greedy method

/*
Assignment:

3. Suppose we assign n persons to n jobs. Let C-ij be the cost of assigning 
   the i-th person to the j-th job.
    a. Use a greedy approach to write an algorithm that finds an assignment that 
       minimizes the total cost of assigning all n persons to all n jobs. Analyze your 
       algorithm and show the results using order notation.

    J1  J2  J3
P1  10  5   5
P2  2   4   10
P3  5   1   7

Show the optimal assignment on the screen.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;

vector<int> greedy_assignment(const vector<vector<int>>& matrix)
{
    int n = matrix.size();
    vector<int> assignments(n, -1); // Initialize assignments with -1

    for (int i = 0; i < n; i++)
    {
        unsigned int minCost = 0xffffffff; // Initialize minCost with max value of unsigned int
        int minJob = -1;

        for (int j = 0; j < n; j++)
        {
            // if job j is not assigned and cost of job j is less than minCost
            // find function returns iterator to end if element is not found  
            if (find(assignments.begin(), assignments.end(), j) == assignments.end() && matrix[i][j] < minCost)
            {
                minCost = matrix[i][j];
                minJob = j;
            }
        }

        assignments[i] = minJob;
    }

    return assignments;
}

int main()
{
    vector<vector<int>> matrix = {
        {10, 5, 5},
        {2, 4, 10},
        {5, 1, 7}
    };

    vector<int> optimalAssignments = greedy_assignment(matrix);

    int totalCost = 0;

    cout << "\n---Greedy method---\n";
    cout << "Optimal assignment:\n";
    for (int i = 0; i < optimalAssignments.size(); i++)
    {
        cout << "P" << i + 1 << " - J" << optimalAssignments[i] + 1 << " - Cost " << matrix[i][optimalAssignments[i]] << "\n";
        totalCost += matrix[i][optimalAssignments[i]];
    }

    cout << "\nTotal cost of assignment: " << totalCost << "\n\n";

    return 0;
}