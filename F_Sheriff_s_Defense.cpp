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
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<vector<ll>> &cnt,vector<ll> &a)
{
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        dfs(nxt, node, adj, cnt, a);
        cnt[node][0] += max(cnt[nxt][0], cnt[nxt][1]);
        cnt[node][1] += max(cnt[nxt][0], cnt[nxt][1] - 2 * c);
    }
    cnt[node][1] += a[node];
}
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        cin >> n >> c;
        vector<ll> a(n);
        fi(0, n) cin >> a[i];
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
        vector<vector<ll>> cnt(n,vector<ll> (2, 0));
        dfs(0,-1,adj,cnt,a);
        cout << max({0LL,cnt[0][0],cnt[0][1]}) <<endl;
    }
    return 0;
}
