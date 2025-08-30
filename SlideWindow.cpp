#include <iostream>
using namespace std;

// SLIDING WINDOW
// 1. Maximum ones
class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size();
        int ans = 0;
        int i = 0; // back pntr
        for (int j = 0; j < n; j++)
        {
            if (nums[j] == 0)
                k--; // when we see zero, decrease k

            while (k < 0)
            {
                if (nums[i] == 0)
                    k++; // as k was decreased only when zero came, and now it is increased only when zero came, it will never go more than initial value
                i++;
            }
            ans = max(j - i + 1, ans);
        }
        return ans;
    }
};

// 2. Longest substring w/o repeating characters
//  use map to store the last seen index of current char, if it existed earlier... and just move left pointer one step ahead of previous index
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int n = s.length();
        int i = 0;
        int ans = 0;
        unordered_map<char, int> mp;
        for (int j = 0; j < n; j++)
        {
            if (mp.find(s[j]) != mp.end())
                i = max(i, mp[s[j]] + 1); // making sure we are only taking rightmost index
            mp[s[j]] = j;
            ans = max(j - i + 1, ans);
        }
        return ans;
    }
};

// 3. Longest repeating character replacement
//  its same as 0,1 question where we have to maximise 1's by flipping atmost 'k' 0's, only difference is here we dont know out of 26 character which one is to be maxmimised hence we will try all possible combinations -> O(26n)
// can be brought down by trying only characters present in the string

class Solution
{
public:
    int solve(string &s, int k, char c)
    {
        int i = 0, maxLen = 0;

        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] != c)
                k--;

            while (k < 0)
            {
                if (s[i] != c)
                    k++;
                i++;
            }
            maxLen = max(maxLen, j - i + 1);
        }
        return maxLen;
    }

    int characterReplacement(string s, int k)
    {
        int ans = 0;
        for (char c = 'A'; c <= 'Z'; c++)
        {
            ans = max(ans, solve(s, k, c));
        }
        return ans;
    }
};

// 4. K cards need to pick from either ends to make sum of values maximum
// can't be done via picking one of the max element from either ends, as it will fail in e.g. 5 5 5 99 1 1 , k=3... via brute force you will pick 5,5,5 hence sum = 15.. which is less than 1,1,99 hence sum = 101,
// approach here is to find min sum of contigous subarray within array, so that remaining k elements can have max sum
class Solution
{
public:
    int maxScore(vector<int> &A, int k)
    {
        int n = A.size();
        int totalsum = 0;
        for (int i : A)
            totalsum += i;

        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; i++)
            pre[i] = pre[i - 1] + A[i - 1];

        int minSubarrSum = totalsum;
        for (int i = n - k; i <= n; i++)
        {
            minSubarrSum = min(minSubarrSum, pre[i] - pre[i - n + k]);
        }
        return totalsum - minSubarrSum;
    }
};

// 5. Subarrays with K Different Integers
class Solution
{
public:
    int atmost(vector<int> &nums, int k)
    {
        if (k == 0)
            return 0;
        int n = nums.size();
        int ans = 0, i = 0;
        unordered_map<int, int> mp;

        for (int j = 0; j < n; j++)
        {
            mp[nums[j]]++;
            while (mp.size() > k)
            {
                mp[nums[i]]--;
                if (mp[nums[i]] == 0)
                    mp.erase(nums[i]);
                i++;
            }
            ans += (j - i + 1);
        }
        return ans;
    }

    int subarraysWithKDistinct(vector<int> &nums, int k)
    {
        int ans = atmost(nums, k) - atmost(nums, k - 1);
        return ans;
    }
};

// 6. Minimum Window Substring
class Solution
{
public:
    string minWindow(string s, string t)
    {
        int n = s.length(), m = t.length();

        int start = 0, end = INT_MAX - 1;

        unordered_map<char, int> tmap, smap;

        for (char c : t)
            tmap[c]++;

        int need = tmap.size();
        int have = 0;
        int i = 0;

        for (int j = 0; j < n; j++)
        {
            smap[s[j]]++;

            if (smap[s[j]] == tmap[s[j]])
                have++;

            while (have == need)
            {
                if (end - start > j - i)
                {
                    end = j;
                    start = i;
                }
                smap[s[i]]--;
                if (tmap.count(s[i]) && smap[s[i]] < tmap[s[i]])
                    have--;
                i++;
            }
        }
        return end != INT_MAX - 1 ? s.substr(start, end - start + 1) : "";
    }
};

// 7. Minimum Window Subsequence
// dp method
string finalans;
bool dp[1001][101];
void solve(string S, string T, string temp, int s, int t)
{
    if (s < 0 || t < 0)
    {
        if (t < 0)
        {
            if (finalans == "" || finalans.length() > temp.length())
                finalans = temp;
        }
        return;
    }
    if (dp[s][t] != false)
        return;

    dp[s][t] = true;

    if (S[s] == T[t])
        solve(S, T, temp + S[s], s - 1, t - 1);

    solve(S, T, temp + S[s], s - 1, t);
}

string minWindow(string S, string T)
{
    finalans = "";

    reverse(S.begin(), S.end());
    reverse(T.begin(), T.end());
    int s = S.length();
    int t = T.length();
    for (int i = s - 1; i >= 0; i--)
    {
        memset(dp, false, sizeof(dp));
        solve(S, T, "", i, t - 1);
    }
    return finalans;
}

// 2 pointer method
string minWindow(string S, string T)
{
    int sLen = S.size(), tLen = T.size();
    int minLen = INT_MAX, startIdx = -1;

    for (int i = 0; i < sLen; ++i)
    {
        if (S[i] != T[0])
            continue;

        int j = 0, k = i;
        // Move forward to match T in S
        while (k < sLen && j < tLen)
        {
            if (S[k] == T[j])
                j++;
            k++;
        }

        if (j == tLen)
        {
            // Now move backward to shrink window
            int end = k - 1;
            j = tLen - 1;
            while (k >= i)
            {
                k--;
                if (S[k] == T[j])
                    j--;
                if (j < 0)
                    break;
            }
            int winStart = k;
            if (end - winStart + 1 < minLen)
            {
                minLen = end - winStart + 1;
                startIdx = winStart;
            }
        }
    }

    return startIdx == -1 ? "" : S.substr(startIdx, minLen);
}


//8. Count pairs whose sum<=upper and sum>=lower
//understand properly
class Solution {
public:
    long long solve(vector<int>& nums, int val)
    {
        int n=nums.size();
        long long ans=0;
        for(int i=0;i<n;i++)
        {
            int ub = upper_bound(nums.begin()+i+1,nums.end(),val-nums[i])-(nums.begin()+i+1);
            //upperbound stops at that element which violates the sum i.e. A[i]+ub_value > required sum
            //hence we will pick all elements just before ub to pair with ith element
            ans+=(ub);
        }
        return ans;
    }
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        //all pairs smaller or equal to upper - smaller or equal to lower-1;
        return  solve(nums,upper)-solve(nums,lower-1);
    }
};

