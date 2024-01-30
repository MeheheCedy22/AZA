// done

/*
Assignment:

Scheduling with Deadlines
Problem : Determine the schedule with maximum total profit given that each job has a profit 
that will be obtained only if the job is scheduled by its deadline.Inputs : n, the number of 
jobs, and array of integers deadline, indexed from 1 to n, where deadline[i] is the deadline 
for the ith job.The array has been sorted in nonincreasing order according to the profits 
associated with the jobs.Outputs : an optimal sequence J for the jobs.

Table 1.1. Consider the following jobs, deadlines, and profits, and use the scheduling with 
deadlines algorithm to maximize the total profit. Show the optimal sequence of jobs with max 
profit on the screen. 

Job  Deadline  Profit
1       2       40
2       4       15
3       3       60
4       2       20
5       3       10
6       1       45
7       1       55

*/


#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::swap;


struct Job {
    int id = 0;
    int deadline = 0;
    int profit = 0;
};


int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

/*
    This quick sort implementation is from https://www.geeksforgeeks.org/quick-sort/
    and adapted to this problem.
     * partition() and qucikSortJobs() functions *
*/
int partition(vector<Job>& jobs, int low, int high)
{
    // Choose pivot
    int pivotIndex = low + rand() % (high - low);
    Job pivot = jobs[pivotIndex];

    // Move pivot to end
    swap(jobs[pivotIndex], jobs[high]);

    // Elements less than pivot will be pushed to the left of pivotIndex
    // Elements more than pivot will be pushed to the right of pivotIndex
    // Equal elements can go either way
    pivotIndex = low;
    for (int i = low; i < high; i++)
    {
        if (jobs[i].profit > pivot.profit)
        {
            swap(jobs[i], jobs[pivotIndex]);
            pivotIndex++;
        }
    }

    // Move pivot to its final place
    swap(jobs[pivotIndex], jobs[high]);

    // Return the pivot index
    return pivotIndex;
}

void quickSortJobs(vector<Job>& jobs, int low, int high)
{
    if (low < high)
    {
        // Partition the array
        int pivot = partition(jobs, low, high);

        // Recursively sort the sub-arrays
        quickSortJobs(jobs, low, pivot);
        quickSortJobs(jobs, pivot + 1, high);
    }
}
/*-------------------------------------------------------------------------------------*/

void printJobsVector(const vector<Job>& jobs)
{
    cout << "\n";
    cout << "Debug print:\n";
    cout << "Job  Deadline  Profit\n";
    for (int i = 0; i < jobs.size(); ++i)
    {
        cout << jobs[i].id << "\t" << jobs[i].deadline << "\t" << jobs[i].profit << "\n";
    }
    cout << "\n";
}

void schedule(int n, const vector<Job>& jobs, vector<int>& J)
{
    vector<Job> sortedJobs = jobs;

    cout <<"\nUnsorted jobs:";
    printJobsVector(sortedJobs);

    // Sort the jobs in non-increasing order of profit
    quickSortJobs(sortedJobs, 0, sortedJobs.size() - 1);

    cout <<"\nSorted jobs:";
    printJobsVector(sortedJobs);

    // Create a vector to represent the schedule, initialized with -1 (unassigned)
    vector<int> schedule(n, -1);

    for (int i = 0; i < n; i++)
    {
        int jobIndex = sortedJobs[i].id - 1; // 0-based index

        for (int slot = minimum(sortedJobs[i].deadline - 1, n - 1); slot >= 0; slot--)
        {
            if (schedule[slot] == -1)
            {
                schedule[slot] = jobIndex;
                break;
            }
        }
    }

    // Copy the final schedule to J (1-based)
    for (int i = 0; i < n; i++)
    {
        J.push_back(schedule[i] + 1);
    }
}

int main()
{
    int n = 7; // Number of jobs
    
    vector<Job> jobs = {
        {1, 2, 40},
        {2, 4, 15},
        {3, 3, 60},
        {4, 2, 20},
        {5, 3, 10},
        {6, 1, 45},
        {7, 1, 55}
    };

/*testing*/
    // vector<Job> jobs = {
    //     {1, 4, 85},
    //     {2, 3, 45},
    //     {3, 2, 30},
    //     {4, 1, 60},
    //     {5, 4, 25},
    //     {6, 5, 70},
    //     {7, 2, 15}
    // };
/*---------*/
    // vector<Job> jobs = {
    //     {1,2,60},
    //     {2,1,30},
    //     {3,2,40},
    //     {4,1,80}
    // };
/*---------*/


    vector<int> J; // To store the optimal schedule
    schedule(n, jobs, J);

    cout << "Optimal schedule for the jobs: ";
    for (int i = 0; i < n; i++)
    {
        if(J[i] > 0)
        {
            cout << J[i] << " ";
        }
    }
    cout << "\n\n";

    return 0;
}