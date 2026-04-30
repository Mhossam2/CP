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
vector<ll> color;
vector<bool> vis;
void dfs(ll node, ll c) {
    vis[node] = true;
    for (ll nei : adj[node]) {
        if (!vis[nei] && color[nei] == c) {
            dfs(nei, c);
        }
    }
}

using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n, m;
        cin >> n;
        adj.resize(n + 1);
        color.resize(n + 1);
        vis.assign(n + 1, false);
        fi(1, n + 1) cin>>color[i];
        for (ll i = 0; i < n-1; i++) {
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ll cnt0 = 0, cnt1 = 0;
        for (ll i = 1; i <= n; i++) {
            if (!vis[i]) {
                if (color[i] == 0) cnt0++;
                else cnt1++;
                dfs(i, color[i]);
            }
        }
        cout<<min(cnt0,cnt1);
    }
    return 0;
}