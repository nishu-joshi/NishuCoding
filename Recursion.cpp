#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// very conceptual questions
// 1. Sorting array with recursion (Aditya video too)
class Solution
{
public:
    void sortStack(stack<int> &s)
    {
        if (s.empty())
            return;

        int top = s.top();
        s.pop();

        sortStack(s); // Recursively sort remaining

        insertSorted(s, top); // Insert top in sorted position
    }

private:
    void insertSorted(stack<int> &s, int val)
    {
        if (s.empty() || val > s.top())
        {
            s.push(val);
            return;
        }

        int temp = s.top();
        s.pop();
        insertSorted(s, val);
        s.push(temp);
    }
};

// 2. Sorting Stack with recursion
void sorting(stack<int> &s, int x)
{
    if (s.empty() || s.top() < x)
    {
        s.push(x);
        return;
    }

    int top = s.top();
    s.pop();

    sorting(s, x);

    s.push(top);
}

void SortedStack ::sort()
{
    if (s.empty())
        return;

    int top = s.top();
    s.pop();

    sort();

    sorting(s, top);
}

// 3. Reverse a stack using recursion
void nichedaldo(stack<int> &s, int x)
{
    if (s.empty())
    {
        s.push(x);
        return;
    } // only when we emptied the stack then we put element, and then put the elements back, just like mitti nikal k beej dalke, wapis as it is mitti dalna

    int top = s.top();
    s.pop();
    nichedaldo(s, x);
    s.push(top);
}

class Solution
{
public:
    void Reverse(stack<int> &s)
    {
        if (s.size() == 1)
            return; // when size is 1 or 0(works in both case), nothing to reverse return as it is.

        int top = s.top();
        s.pop();

        Reverse(s); // will reverse the existing stack called

        nichedaldo(s, top); // will put the recent top element to the bottom of stack
    }
};

// 4. kth symbol of grammar
class Solution
{
public:
    int kthGrammar(int n, int k)
    {
        if (n == 1)
            return 0;

        int parentvalue = kthGrammar(n - 1, (k + 1) / 2);

        if ((k % 2 && parentvalue) || (!(k % 2) && !parentvalue))
            return 1;
        else
            return 0;
    }
};

// 5. Tower of hanoi
void solve(int n, int from, int to, int aux, int &count)
{
    if (n == 1)
    {
        count++;
        return;
    }

    solve(n - 1, from, aux, to, count); // Move n-1 disks from 'from' to 'aux'

    count++; // Move nth disk from 'from' to 'to'

    solve(n - 1, aux, to, from, count); // Move n-1 disks from 'aux' to 'to'
}

class Solution
{
public:
    int towerOfHanoi(int n, int from, int to, int aux)
    {
        int count = 0;
        solve(n, from, to, aux, count);
        return count;
    }
};
