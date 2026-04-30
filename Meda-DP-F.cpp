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
ll n,c;
ll dp[101][ll(1e5+1)];
ll dfs(ll i, ll w, vector<pair<ll,ll>> &item){
    if(i == n) return 0;
    if(dp[i][w] != -1) return dp[i][w];
    ll ans = 0;
    if(w+item[i].first <= c){
        ans = max(ans, item[i].second + dfs(i+1,w+item[i].first, item));
    }
    ans = max(ans, dfs(i+1, w, item));
    return dp[i][w] = ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin>>n>>c;
        vector<pair<ll,ll>> item(n);
        fi(0,n){
            ll x,y;cin>>x>>y;
            item[i].first=x;
            item[i].second=y;
        }
        vector<vector<ll>> dp(n+1,vector<ll> (c+1,0));
        for(ll i=n-1;i>=0;i--){
            for(ll j=0;j<=c;j++){
                if(j + item[i].first <= c)
                dp[i][j]=max(dp[i][j], item[i].second);
                dp[i][j] = max(dp[i][j], dp[i+1][j]);  
            }
        }
        cout<<dp[0][0];
        //memset(dp, -1, sizeof(dp));
        //cout<<dfs(0,0,item);
    }
    return 0;
}
