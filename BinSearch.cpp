#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// 1. Simple binary search in sorted arrary, if target didnt find then return -1
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int n = nums.size();
        int i = 0, j = n - 1;
        int mid = -1;
        while (j >= i)
        {
            mid = i + (j - i) / 2;

            if (nums[mid] == target)
                return mid;

            else if (nums[mid] < target)
                i = mid + 1;
            else
                j = mid - 1;
        }
        return i > j ? -1 : mid;
    }
};

// 2. Peak element
class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return 0;

        int i = 0, j = n - 1;
        int mid = -1;

        while (left <= right)
        {
            mid = i + (j - i) / 2;

            // Handle boundary cases first
            if (mid == 0)
            {
                if (nums[0] > nums[1])
                    return 0;
                else
                    left = mid + 1;
            }
            else if (mid == n - 1)
            {
                if (nums[n - 1] > nums[n - 2])
                    return n - 1;
                else
                    right = mid - 1;
            }
            else
            {
                if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
                    return mid;
                else if (nums[mid] < nums[mid + 1])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return mid; // guaranteed to be valid due to problem constraints
    }
};

// 3. Search in sorted 2D matrix
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &A, int val)
    {
        int n = A.size(), m = A[0].size();

        int i = 0, j = n - 1, mid = 0;
        while (i <= j)
        {
            mid = i + (j - i) / 2;
            if (A[mid][0] == val)
                return true;
            else if (A[mid][0] > val)
                j = mid - 1;
            else
                i = mid + 1;
        }

        if (j < 0)
            return false; // val is smaller than all row starts
        int roww = j;
        i = 0, j = m - 1, mid = 0;
        while (i <= j)
        {
            mid = i + (j - i) / 2;
            if (A[roww][mid] == val)
                return true;
            else if (A[roww][mid] > val)
                j = mid - 1;
            else
                i = mid + 1;
        }
        return false;
    }
};

// 4. Allocate min number of books
bool isValid(vector<int> &A, int maxPages, int B)
{
    int students = 1;
    int currentSum = 0;

    for (int pages : A)
    {
        if (pages > maxPages)
            return false;

        if (currentSum + pages > maxPages)
        {
            students++;
            currentSum = pages;
        }
        else
        {
            currentSum += pages;
        }
    }

    return students <= B; // allow <= since we try to minimize
}

int Solution::books(vector<int> &A, int B)
{
    int n = A.size();
    if (n < B)
        return -1;

    int low = *max_element(A.begin(), A.end());
    int high = 0;
    for (auto x : A)
        high += x;
    int result = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (isValid(A, mid, B))
        {
            result = mid;
            high = mid - 1; // minimize further
        }
        else
        {
            low = mid + 1;
        }
    }

    return result;
}

// 5. Place k extra stations between given positions in array A to minimize the maximum distance between any two adjacent stations.