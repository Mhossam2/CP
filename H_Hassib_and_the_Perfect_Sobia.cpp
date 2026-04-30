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
using namespace std;
const int N = 100005;
ll n, m;
void dfs1(ll node, ll par, vector<ll> &v, vector<vector<ll>> &adj, vector<ll> &out)
{
    out[node] = v[node];
    for (auto it : adj[node])
    {
        if (it != par)
        {
            dfs1(it, node, v, adj, out);
            out[node] = max(out[node], out[it] - m);
        }
    }
}
void dfs2(ll node, ll par, vector<ll> &v, vector<vector<ll>> &adj, vector<ll> &out)
{
    for (auto it : adj[node])
    {
        if (it != par)
        {
            out[it] = max(out[it], out[node] - m);
            dfs2(it, node, v, adj, out);
        }
    }
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> m;
        vector<ll> v(N), out(N);
        vector<vector<ll>> adj(N);
        fi(1, n + 1) cin >> v[i];
        fi(0, n - 1)
        {
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs1(1, 0, v, adj, out);
        dfs2(1, 0, v, adj, out);
        fi(1, n + 1) cout << out[i] << " ";
        cout << endl;
    }
    return 0;
}
