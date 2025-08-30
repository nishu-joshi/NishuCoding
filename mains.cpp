#include <iostream>
#include<unordered_set>
#include<map>
#include<set>
#define pii pair<int,int>
using namespace std;



int main()
{
    vector<int> A={1,2,4,4,6,8,9,10,11,33};
    auto ans = upper_bound(A.begin(),A.end(),44)-A.begin();
    cout<<"Final ans = "<<ans;
    
    return 0;
}


