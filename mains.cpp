#include <iostream>
#include<unordered_set>
#include<map>
#include<set>
#define pii pair<int,int>
using namespace std;

void solve(int r, int c)
{
    if(r==9)
    {
        cout<<"thak gya hu bro"<<'\n';
        return ;
    }
    
    r+=(c/9);
    c%=9;
    cout<<"r = "<<r<<", c = "<<c<<endl;
    solve(r,c+1);
}

int main()
{
    //vector<vector<char>>A={{}};
    // Solution s;
    // s.solveSudoku(A);
    //cout<<"Final ans = "<<ans;
    solve(0,0);

    
    return 0;
}


