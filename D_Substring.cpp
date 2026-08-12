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
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        set<ll> ss;
        vector<vector<ll>> adj(n);
        vector<ll> root(n, 0);
        fi(0, m)
        {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            ss.insert(u);
            ss.insert(v);
            root[v] = 1;
            adj[u].push_back(v);
        }
        vector<ll> vis(n, 0);
        vector<vector<ll>> dp(n, vector<ll>(26, 0));
        vector<ll> topo;
        bool finish = 0;
        auto dfs = [&](auto &&self, ll u) -> void
        {
            vis[u] = 1;
            for (ll v : adj[u])
            {
                if (vis[v] != 2)
                {
                    if (vis[v] == 1)
                    {
                        finish = 1;
                        return;
                    }
                    self(self, v);
                }
            }
            topo.push_back(u);
            vis[u] = 2;
        };
        fi(0, n)
        {
            if (!root[i])
                dfs(dfs, i);
        }
        reverse(all(topo));
        for (ll i : ss)
        {
            if (vis[i] == 0)
                finish = 1;
        }
        if (finish)
        {
            cout << -1 << endl;
            continue;
        }
        for(ll i:topo){
            dp[i][s[i]-'a']++;
            for(ll ch : adj[i])
            fj(0,26){
                dp[ch][j] = max(dp[i][j], dp[ch][j]);
            }
        }
        ll mx = 0;
        fi(0, n)
        {
            fj(0, 26)
            {
                mx = max(mx, dp[i][j]);
                // cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
            }
        }
        cout << mx;
    }
    return 0;
}
