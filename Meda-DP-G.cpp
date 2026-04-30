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
ll dfs(ll i,ll v, vector<pair<ll,ll>> &item){
    if(v == 0) return 0;
    if(i == n) return 1e18;
    if(dp[i][v] != -1) return dp[i][v];
    ll ans=1e18;
    ans = min(ans, dfs(i + 1, v, item)); //leave item
    if(v - item[i].second >= 0)
    ans = min(ans, item[i].first + dfs(i + 1, v - item[i].second, item)); //take item
    return dp[i][v] = ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> c;
        vector<pair<ll, ll>> item(n);
        fi(0,n){
            ll x,y; cin>>x>>y;
            item[i]={x,y};
        }
        memset(dp, -1, sizeof(dp));
        ll maxv=0;
        fj(0,1e5+1){
            if(dfs(0, j, item) <= c){
                maxv = j;
            }
        }
        cout<<maxv<<endl;
    }
    return 0;
}