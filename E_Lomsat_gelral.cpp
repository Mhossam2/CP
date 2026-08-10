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
const int OO = 1e9 + 5;
const int N = 2e5 + 5;

vll adj[N];
ll c[N], sz[N], big[N];
ll freq[N], mx;
ll sum[N], ans[N];

void pre(ll v, ll p) //to calculate the subtree size and the heavy child
{
    sz[v] = 1;
    for (ll u : adj[v])
        if (u != p)
        {
            pre(u, v);
            sz[v] += sz[u];
            if (big[v] == 0 || sz[u] > sz[big[v]])
                big[v] = u;
        }
}

void upd(ll col, ll d) // the function you change the most depending on the question
{
    if (freq[col] + d > mx)
        mx++;
    else if (freq[col] == mx && sum[freq[col]] == col)
        mx--;

    sum[freq[col]] -= col;
    freq[col] += d;
    sum[freq[col]] += col;
}

void collect(ll v, ll p, ll d) //merging all light childs
{
    upd(c[v], d);
    for (ll u : adj[v])
        if (u != p)
        {
            collect(u, v, d);
        }
}

void dfs(ll v, ll p, bool keep)
{
    for (ll u : adj[v])
        if (u != p && u != big[v])
        {
            dfs(u, v, false);
        }
    // add to DS
    if (big[v] != 0)
        dfs(big[v], v, true);
    upd(c[v], 1);
    for (ll u : adj[v])
        if (u != p && u != big[v])
            collect(u, v, +1); // light/small subtrees

    // answer queries
    ans[v] = sum[mx];

    // remove from DS
    if (!keep)
        collect(v, p, -1);
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        for (ll i = 1; i <= n; ++i)
            cin >> c[i];

        ll a, b;
        for (ll i = 0; i < n - 1; ++i)
        {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        pre(1, 1);
        dfs(1, 1, true);
        for (ll i = 1; i <= n; ++i)
            cout << ans[i] << ' ';
    }
    return 0;
}