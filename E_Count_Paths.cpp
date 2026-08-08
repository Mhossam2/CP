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
vector<ll> a;
vector<vector<ll>> adj;
long long ans;
vector<map<ll, ll>> cnt;
void dfs(ll v, ll p)
{
    ll bst = -1;
    for (ll u : adj[v])
        if (u != p)
        {
            dfs(u, v);
            if (cnt[v].size() < cnt[u].size())
            {
                swap(cnt[v], cnt[u]);
            }
            for (auto [x, y] : cnt[u])
            {
                if (x != a[v])
                {
                    ans += cnt[v][x] * y;
                }
                cnt[v][x] += y;
            }
        }
    ans += cnt[v][a[v]];
    cnt[v][a[v]] = 1;
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

        a.resize(n);
        fi(0, n) cin >> a[i];
        adj.assign(n, {});
        fi(0, n - 1)
        {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ans = 0;
        cnt.assign(n, {});
        dfs(0, -1);
        cout << ans << endl;
    }
    return 0;
}
