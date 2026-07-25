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
vector<vector<ll>> adj;
vector<ll> subtreeSize;

ll dfs(ll node, ll parent) {
    ll size = 1;
    for (ll child : adj[node]) {
        if (child != parent) {
            size += dfs(child, node);
        }
    }
    subtreeSize[node] = size;
    return size;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n,k;cin>>n>>k;
        adj.assign(n+1,{});
        subtreeSize.assign(n+1,0);
        vector<pair<ll,ll>> edges(n-1);
        fi(0,n-1){
            ll x,y;cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
            edges[i].first=x;
            edges[i].second=y;
        }
        dfs(1,0);
    }
    return 0;
}
