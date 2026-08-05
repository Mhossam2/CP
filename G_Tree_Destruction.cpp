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
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<pair<ll, ll>> &ans)
{

    ans[node].first = adj[node].size();
    ll mx1 = -1;
    ll mx2 = -1;
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        dfs(nxt, node, adj, ans);
        if (ans[node].first < ans[nxt].first + adj[node].size() + 2)
        {
            ans[node].first = ans[nxt].first + adj[node].size() + 2;
        }
        mx2 = max(mx2, ans[nxt].first);
        if (mx2 > mx1)
            swap(mx1, mx2);
    }
    ans[node].second = ans[node].first;
    if (mx2 != -1)
    {
        ans[node].second = mx1 + mx2 + adj[node].size() - 4;
    }
}
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<vector<ll>> adj(n);
        fi(0, n - 1)
        {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<pair<ll, ll>> ans(n, {0, 0});
        dfs(0, 0, adj, ans);
        ll mx = 0;
        fi(0, n)
        {
            mx = max({mx, ans[i].first, ans[i].second});
        }
        cout << mx << endl;
    }
    return 0;
}
