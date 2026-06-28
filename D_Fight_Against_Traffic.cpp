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
ll modPow(ll a, ll b, ll mod)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod; // O( log b )
        b >>= 1;
    }
    return res;
}
ll modInverse(ll n, ll mod)
{
    return modPow(n, mod - 2, mod);
}

ll n, d;
bool vis[100001];
bool dp[100001]; // dp[new_rem] = min(dp[new_rem], dp[oldrem]+1)
bool dfs(ll val, string &ans)
{
    if (vis[val])
        return dp[val];
    vis[val] = 1;
    if (val == 0)
        return 1;
    ll res = 0;
    res |= dfs((val * 10) % n, ans);
    if (res)
    {
        ans += "0";
        return dp[val] = res;
    }
    res |= dfs((val * 10 + d) % n, ans);
    ans += to_string(d);
    return dp[val] = res;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n,m,s,t;cin>>n>>m>>s>>t;
        vector<vector<ll>> adj(n+1);
        fi(0,m){
            ll u,v;cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        auto bfs = [&](ll root){
            vector<ll> dist(n,1e18);
            queue<ll> q;
            dist[root] = 0;
            q.push(root);
            while(!q.empty()){
                ll cur = q.front(); q.pop();
                for(ll nxt:adj[cur]){
                    if(dist[nxt]>dist[cur]+1){
                        dist[nxt]=dist[cur]+1;
                        q.push(nxt);
                    }
                }
            }
            return dist;
        };
        vector<ll> sd = bfs(s);
        vector<ll> td = bfs(t);
        
    }
    return 0;
}
