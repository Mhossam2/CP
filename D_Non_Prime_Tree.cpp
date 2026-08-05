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
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<ll> &ans, ll &lst)
{
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        ans[nxt] = lst + 1;
        while ((abs(ans[nxt] - ans[node]) != 1) && ( (abs(ans[nxt] - ans[node]) % 2 != 0) || (abs(ans[nxt] - ans[node]) == 2)))
            ans[nxt]++;
        lst = ans[nxt];
        dfs(nxt, node, adj, ans, lst);
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
        vector<ll> ans(n, 1);
        ll lst=1;
        dfs(0, -1, adj, ans, lst);
        fi(0, n) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
