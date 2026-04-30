#include <bits/stdc++.h>
using namespace std;
#define HONDA                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
typedef long double ld;
typedef long long ll;
#define mpll map<ll, ll>
#define vll vector<ll>
#define all(a) a.begin(), a.end()
#define fi(ii, n) for (ll i = ii; i < n; i++)
#define fj(jj, n) for (ll j = jj; j < n; j++)
#define fit(c) for (auto it = c.begin(); it != c.end(); ++it)
#define endl "\n"
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
inline bool in(int i, int j, int rows, int cols)
{
    return i >= 0 && i < rows && j >= 0 && j < cols;
}
inline bool in(int i, int l, int h)
{
    return i >= l && i <= h;
}
ll n,k;
ll dp[ll(1e5+1)];
ll dfs(ll i, vector<ll> &cost){
    if(i == n-1) return 0;
    if(dp[i] != -1) return dp[i];
    ll ans = 1e9;
    for(ll j=1;j<=k;j++){
        if(i<n-j){
            ans=min(ans, dfs(i+j,cost) + abs(cost[i]-cost[i+j]));
        }
    }
    return dp[i]= ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin>>n>>k;
        vector<ll> cost(n);
        fi(0,n){
            cin>>cost[i];
        }
        memset(dp, -1, sizeof(dp));
        cout<<dfs(0,cost);
//
    }
    return 0;
}