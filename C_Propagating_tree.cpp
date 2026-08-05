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
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<ll> &discover, vector<ll> &begin, vector<ll> &finish, vector<ll> &depth)
{
    discover.push_back(node);
    begin[node] = discover.size();
    for(ll nxt : adj[node]){
        if(nxt == parent) continue;
        depth[nxt] = depth[node]+1;
        dfs(nxt,node,adj,discover,begin,finish,depth);
    }
    finish[node] = discover.size();
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
        vector<ll> depth(n,0), begin(n), finish(n), discover;
        dfs(0, 0, adj, discover,begin,finish,depth);
        vll inc,dec;
        fi(0,n){
            
        }
    }
    return 0;
}
