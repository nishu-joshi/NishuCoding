#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;

// 1. Frog Jump
//  at ith index we have 2 option either frog had jumped from i-2 or from i-1, take min cost of both cases and proceed
class Solution
{
public:
    int minCost(vector<int> &H)
    {
        int n = H.size();

        int dp[100001];
        memset(dp, 0, sizeof(dp));
        dp[0] = 0;
        dp[1] = abs(H[1] - H[0]);

        for (int i = 2; i <= n; i++)
        {
            dp[i] = min(dp[i - 2] + abs(H[i] - H[i - 2]), dp[i - 1] + abs(H[i] - H[i - 1]));
        }
        return dp[n - 1];
    }
};

// 2. Longest common substring
class Solution
{
public:
    int longestCommonSubstr(string &x, string &y)
    {
        int n = x.length();
        int m = y.length();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        int res = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (x[i - 1] == y[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = 0;
                res = max(dp[i][j], res);
            }
        }
        return res;
    }
};

// 3. Distinct subsequences
//  always think of reursion first, then memoize it, same pattern will be followed by table
class Solution
{
public:
    int numDistinct(string s, string t)
    {
        int n = s.length();
        int m = t.length();
        unsigned int dp[1001][1001];

        memset(dp, 0, sizeof(dp));

        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[n][m];
    }
};

// int static dp[1001][1001];
// class Solution {
// public:
//     int solve(string s, string t, int i, int j)
//     {
//         if(i<0 && j>=0) return 0;
//         if(j<0) return 1;
//         if(dp[i][j]!=-1) return dp[i][j];

//         if(s[i]==t[j]) return dp[i][j]=solve(s,t,i-1,j-1)+solve(s,t,i-1,j);
//         return dp[i][j]=solve(s,t,i-1,j);
//     }

//     int numDistinct(string s, string t) {
//         int n=s.length();
//         int m=t.length();
//         memset(dp,-1,sizeof(dp));
//         return solve(s,t,n-1,m-1);
//     }
// };

// 4. Edit distance
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.length();
        int m = word2.length();
        int dp[501][501];
        memset(dp, 0, sizeof(dp));

        for (int j = 0; j <= m; j++)
            dp[0][j] = j; // word1 = "", add all elements from word2
        for (int i = 0; i <= n; i++)
            dp[i][0] = i; // word2 = "", delete all elements from word1

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = min(dp[i - 1][j - 1], 1 + dp[i - 1][j]);
                else
                    dp[i][j] = 1 + min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]);
            }
        }
        return dp[n][m];
    }
};

// int static dp[501][501];
// class Solution {
// public:
//     int solve(string s, string t, int i, int j)
//     {
//         if(j<0) return i+1;
//         if(i<0) return j+1;
//         if(dp[i][j]!=-1) return dp[i][j];
//         if(s[i]==t[j]) return dp[i][j]=min(solve(s,t,i-1,j-1),1+solve(s,t,i-1,j));

//         return dp[i][j]=1+min(min(solve(s,t,i,j-1), solve(s,t,i-1,j)), solve(s,t,i-1,j-1));
//     }
//     int minDistance(string s, string t) {
//         int n=s.length();
//         int m=t.length();
//         if(n==0) return m;
//         if(s==t) return 0;
//         memset(dp,-1,sizeof(dp));
//         return solve(s,t,n-1,m-1);
//     }
// };


//5. Wildcard matching
static signed char dp[2001][2001];
class Solution {
public:
    int solve(string s, string p, int i, int j)
    {
        if(i<0 && j<0) return true;
        if(j<0) return false;
        if(i<0)
        {
            if(p[j]=='*') return solve(s,p,i,j-1);
            else return false;
        } 
        if(dp[i][j]!=-1) return dp[i][j];
        
        if(s[i]==p[j] || p[j]=='?') return dp[i][j]=solve(s,p,i-1,j-1);

        if(p[j]=='*')
        {
            return dp[i][j]=solve(s,p,i,j-1)||solve(s,p,i-1,j);
            // match character, skips * , use * to keep matching characters
        }
        else return dp[i][j]=0;
        
    }
    bool isMatch(string s, string p) {
        int n=s.length();
        int m=p.length();
        memset(dp,-1,sizeof(dp));
        return solve(s,p,n-1,m-1);
    }
};

//6. Best Time to Buy and Sell Stock IV
int static dp[1001][201];
class Solution {
public:
    int solve(vector<int>& prices, int i, int k)
    {
        if(k==0) return 0;

        if(i<0 && k%2) return -10000;

        if(i<0) return 0;
        
        if(dp[i][k]!=-1) return dp[i][k];

        if(k%2) return dp[i][k]=max(solve(prices,i-1,k-1)+prices[i], solve(prices,i-1,k));
        else return dp[i][k]=max(solve(prices,i-1,k-1)-prices[i], solve(prices,i-1,k));

    }
    int maxProfit(int allTra , vector<int>& prices) {
        int k=2*allTra; 
        //k even means have to buy... k odd means have to sell 
        int n=prices.size();
        reverse(prices.begin(),prices.end());
        memset(dp,-1,sizeof(dp));
        int ans  = solve(prices,n-1,k);
        return ans>=0 ? ans:0;
    }
};