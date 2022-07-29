#include<bits/stdc++.h>
using namespace std;

string s,ss;
int dp[1000][1000];

int LCS(int n,int m)
{
    if(n < 0 || m < 0) return 0;
    if(dp[n][m] != -1) return dp[n][m];
    if(s[n] == ss[m]) return dp[n][m] = 1 + LCS(n-1,m-1);
    return dp[n][m] = max(LCS(n,m-1),LCS(n-1,m));
}

int main()
{
    int t;
    cin >> t;

    while(t--){
        int n,m;

        cin >> s >> ss;

        n = s.size();
        m = ss.size();

        memset(dp,-1,sizeof dp);
        cout << LCS(n-1,m-1) <<endl;
    }

    return 0;
}
