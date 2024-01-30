// done

/*
Assignment:

1. Design and implement an algorithm to solve a problem for scheduling with deadlines 
(Algorithm 4.4).    

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

2. Consider the procedure schedule in the Scheduling with Deadlines algorithm (Algorithm 4.4). 
Let d be the maximum of the deadlines for n jobs. Modify the procedure so that it adds a job 
as late as possible to the schedule being built, but no later than its deadline. Do this by 
initializing d+1 disjoint sets, containing the integers 0, 1, ..., d. Let small(S) be the 
smallest member of set S. When a job is scheduled, find the set S containing the minimum of its 
deadline and n. If small(S) = 0, reject the job. Otherwise, schedule it at time small(S), and 
merge S with the set containing small(S)−1. Assuming we use Disjoint Set Data Structure III in 
Appendix C, show that this version is θ(nlgm), where m is the minimum of d and n. 

*/

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::swap;


struct Job{
    int id = 0;
    int deadline = 0;
    int profit = 0;
};

/*
    Data structure is from https://www.geeksforgeeks.org/job-sequencing-problem-using-disjoint-set/
    and adapted to this problem.
*/
struct DisjointSet{
    int *parent;
 
    // Constructor
    DisjointSet(int n)
    {
        parent = new int[n+1];
 
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    ~DisjointSet()
    {
        delete[] parent;
    }
 
    int find(int s)
    {
        if (s == parent[s])
        {
            return s;
        }

        return parent[s] = find(parent[s]);
    }
 
    // Makes u as parent of v.
    void merge(int u, int v)
    {
        //update the greatest available
        //free slot to u
        parent[v] = u;
    }
};

int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

int findMaxDeadline(vector<Job> jobs, int n)
{
    int result = -2147483648; // int MIN
    for (int i = 0; i < n; i++)
    {
        result = maximum(result, jobs[i].deadline);
    }

    return result;
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
/*--------------------------------------------------------------------------*/

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

/*
    Parts of schedule function are from https://www.geeksforgeeks.org/job-sequencing-problem-using-disjoint-set/
    and are adapted to this problem.
*/
void schedule(int n, const vector<Job>& jobs)
{
    vector<Job> sortedJobs = jobs;

    cout <<"\nUnsorted jobs:";
    printJobsVector(sortedJobs);

    // Sort the jobs in non-increasing order of profit
    quickSortJobs(sortedJobs, 0, sortedJobs.size() - 1);

    cout <<"\nSorted jobs:";
    printJobsVector(sortedJobs);


    int maxDeadline = findMaxDeadline(sortedJobs, n);
    DisjointSet disSet(maxDeadline);

    vector <int> jobsByDeadline(maxDeadline, -1);
    cout << "Jobs by profits:\n";

    // core of the algorithm
    for (int i = 0; i < n; i++)
    {
        int availableSlot = disSet.find(sortedJobs[i].deadline);

        if (availableSlot > 0)
        {
            disSet.merge(disSet.find(availableSlot - 1), availableSlot);
 
            cout << sortedJobs[i].id << " ";
            jobsByDeadline[availableSlot - 1] = sortedJobs[i].id;
        }
    }

    cout << "\nJobs by deadline:\n";
    for (int i = 0; i < maxDeadline; i++)
    {
        cout << jobsByDeadline[i] << " ";
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
// int n = 7; // Number of jobs
//
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


    schedule(n, jobs);

    return 0;
}