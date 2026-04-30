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
ll n, h,m;
vector<vector<ll>> dp(3002, vector<ll> (3002, -1));
vector<ll> ah,am;
ll dfs(ll i, ll magic){
    if(i == n) return 0;
    if(dp[i][magic] != -1) return dp[i][magic];
    ll ans = 1e18;
    if(magic + am[i] <= m)
    ans=min(ans, dfs(i + 1, magic + am[i]));
    ans=min(ans, dfs(i + 1, magic) + ah[i]);
    return dp[i][magic]=ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> h >> m;
        fi(0,n){
            ll x,y;cin>>x>>y;
            ah.push_back(x);
            am.push_back(y);
        }
        ll ans=0;
        dfs(0,m);
        fi(0, n + 1){
            fj(0, m + 1){
                if(dfs(i,j) <= h) ans=i;
            }
        }
        cout << ans;
    }
    return 0;
}