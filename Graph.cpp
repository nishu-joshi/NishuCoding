#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<set>
using namespace std;


//1. Undirected graph has cycle or not?
//if neighbour node is visited and it is not parent node -> cycle is present
//means some other way is present to reach that neigbour node
bool bfs(vector<vector<int>>&adj,vector<bool>&vis,int node)
{
    queue<int>q;
    unordered_map<int,int>parent;// key is child of data
    q.push(node);
    parent[node]=-1;
    vis[node]=true;
    
    while(!q.empty())
    {
        int front=q.front();
        q.pop();
        
        for(int i=0;i<adj[front].size();i++)
        {
            int child = adj[front][i];
            if(!vis[child])
            {
                q.push(child);
                vis[child]=true;
                parent[child]=front;
            }
            else if(vis[child] && parent[front]!=child) return true;//is node is visited and is not parent return cycle is present
        }
    }
    return false;
}

class Solution {
  public:
    bool isCycle(int nodes, vector<vector<int>>& edges) {
        vector<vector<int>>adj(nodes,vector<int>());
        
        for(auto x : edges)
        {
            adj[x[0]].push_back(x[1]);
            adj[x[1]].push_back(x[0]);   
        }
        
        vector<bool>vis(nodes,false);
        
        for(int i=0;i<nodes;i++)
        {
            if(!vis[i])
            {
                if(bfs(adj,vis,i)==true) return true;
            }
        }
        return false;
    }
};


//2. Word ladder
class Solution {
public:
 int ladderLength(string beg, string endd, vector<string>& wordList) {
    unordered_set<string>mp,vis;

    for(auto s:wordList) mp.insert(s);

    queue<pair<string,int> >q;
    
    q.push({beg,1});
    vis.insert(beg);
    int depth;

    while(!q.empty())
    {
        auto front=q.front();
        q.pop();
        string frontword=front.first;
        string temp;
        depth=front.second;

        if(frontword==endd) return depth;

        for(int i=0;i<frontword.length();i++)
        {
            temp=frontword;
            for(int j=0;j<26;j++)
            {
                temp[i]='a'+j;
                if(mp.count(temp) && !vis.count(temp))
                {
                    q.push({temp,depth+1});
                    vis.insert(temp);
                }
                temp=frontword;
            }
        }
    }
    return 0;
}
};



//3. Number of distinct islands
class Solution {
     public:
    set<vector<pair<int,int>>>sett;
    void solve(vector<vector<int>>& grid,vector<vector<bool>>& vis, int i, int j, int bi, int bj, int n, int m,                     vector<pair<int,int>>&tempr)
    {
        if(i<0 || j<0 ||i>=n || j>=m || vis[i][j] || grid[i][j]!=1) return ;
        
        vis[i][j]=true;
        tempr.push_back({bi,bj});
        
        solve(grid,vis,i+1,j,bi+1,bj,n,m,tempr);
        solve(grid,vis,i,j+1,bi,bj+1,n,m,tempr);
        solve(grid,vis,i,j-1,bi,bj-1,n,m,tempr);
        solve(grid,vis,i-1,j,bi-1,bj,n,m,tempr);
    }
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
    
        vector<vector<bool>>vis(n,vector<bool>(m,false));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!vis[i][j] && grid[i][j]==1)
                {
                    vector< pair<int,int> >tempr;
                    solve(grid,vis,i,j,0,0,n,m,tempr);
                    sett.insert(tempr);
                }
            }
        }
        return sett.size();
    }
};
