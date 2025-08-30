#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// 1. Next greater to left
class Solution
{
public:
    vector<int> nextGreaterToLeft(vector<int> &nums)
    {
        vector<int> ans;
        stack<int> st;

        for (int num : nums)
        {
            while (!st.empty() && st.top() <= num)
                st.pop();

            ans.push_back(st.empty() ? -1 : st.top());
            st.push(num);
        }

        return ans;
    }
};

// 2. Stock span problem
class Solution
{
public:
    vector<int> calculateSpan(vector<int> &prices)
    {
        int n = prices.size();
        vector<int> ans(n);
        stack<pair<int, int>> s; // {price, index}

        for (int i = 0; i < n; i++)
        {
            while (!s.empty() && s.top().first <= prices[i])
                s.pop();

            if (!s.empty())
                ans[i] = i - s.top().second;
            else
                ans[i] = i + 1;

            s.push({prices[i], i});
        }
        return ans;
    }
};

// 3. Maximum histogram area
class Solution
{
public:
    int largestRectangleArea(vector<int> &v)
    {
        int n = v.size();
        vector<int> nsl(n, -1), nsr(n, -1);

        stack<pair<int, int>> st;

        for (int i = n - 1; i >= 0; i--)
        {
            while (!st.empty() && st.top().first >= v[i])
                st.pop();

            if (!st.empty() && st.top().first < v[i])
                nsr[i] = st.top().second;
            else
                nsr[i] = n;

            st.push({v[i], i});
        }

        while (!st.empty())
            st.pop();

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && st.top().first >= v[i])
                st.pop();

            if (!st.empty() && st.top().first < v[i])
                nsl[i] = st.top().second;
            else
                nsl[i] = -1;

            st.push({v[i], i});
        }

        int ans = INT_MIN;

        for (int i = 0; i < n; i++)
            ans = max(v[i] * (nsr[i] - nsl[i] - 1), ans);

        return ans;
    }
};

// 4. Trapping rainwater
class Solution
{
public:
    int trap(vector<int> &v)
    {
        int n = v.size();
        vector<int> left(n, v[0]), right(n, v[n - 1]);

        for (int i = 1; i < n; i++)
        {
            left[i] = max(left[i - 1], v[i]);
        }

        for (int i = n - 2; i >= 0; i--)
        {
            right[i] = max(right[i + 1], v[i]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            ans += abs(v[i] - min(left[i], right[i]));
        }
        return ans;
    }
};
