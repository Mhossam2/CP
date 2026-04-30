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
ll MOD;
ll modPow(ll a, ll b , ll mod)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod ; 
        a = (a * a) % mod; //               O( log b )
        b >>= 1;
    }
    return res;
}
ll modInverse(ll n, ll mod)
{
    return modPow(n, mod - 2, mod) ;
}
string s="0";
struct lca_tree
{
private:
    ll n;
    ll LOG = 20;
    vector<vector<ll>> adj;
    vector<vector<ll>> up;
    vector<vector<ll>> updigits;
    vector<vector<ll>> updigitsr;

    vector<ll> depth;

    // Time Complexity: O(V * LOG) where V is the number of vertices.
    // Returns: void.
    // Description: Precomputes the 'up' table for binary lifting and calculates the 'depth' of each node.
    void dfs(ll node, ll parent)
    {
        up[node][0] = parent;
        updigits[node][0] = s[node]-'0';
        updigitsr[node][0] = s[node]-'0';
        for (ll i = 1; i < LOG; i++)
        {
            if (up[node][i - 1] != -1){
                up[node][i] = up[up[node][i - 1]][i - 1];
                updigits[node][i] = (((updigits[node][i-1])%MOD*modPow(10,(1LL << (i-1)),MOD))%MOD + updigits[up[node][i-1]][i-1]%MOD)%MOD;
                updigitsr[node][i] = (((updigitsr[node][i-1])%MOD + updigitsr[up[node][i-1]][i-1]%MOD *modPow(10,(1LL << (i-1)),MOD))%MOD)%MOD;
            }
            else{
                up[node][i] = -1;
                updigits[node][i] = -1;
                updigitsr[node][i] = -1;
            }
        }
        for (ll i = 0; i < adj[node].size(); i++)
        {
            auto to = adj[node][i];
            if (to == parent)
            {
                continue;
            }
            depth[to] = depth[node] + 1;
            dfs(to, node);
        }
    }

public:
    // Time Complexity: O(V * LOG) for the initial build.
    // Returns: Constructor (No return type).
    // Description: Initializes the tree sizes, arrays, and starts the DFS from the root.
    lca_tree(ll nodes, vector<vector<ll>> &tree_adj, ll root)
    {
        n = nodes;
        adj = tree_adj;
        up = vector<vector<ll>>(n, vector<ll>(LOG, -1));
        updigits = vector<vector<ll>>(n, vector<ll>(LOG));
        updigitsr = vector<vector<ll>>(n, vector<ll>(LOG));
        depth = vector<ll>(n, 0);

        // depth of root is 0, parent of root is -1
        dfs(root, -1);
    }

    // Time Complexity: O(LOG).
    // Returns: ll (The k-th ancestor of the given node, or -1 if the ancestor doesn't exist).
    // Description: get kth ancestor using binary lifting.
    ll lift(ll node, ll k)
    {
        for (ll i = 0; i < LOG; i++)
        {
            if (k & (1 << i))
            {
                node = up[node][i];
                if (node == -1)
                    break;
            }
        }
        return node;
    }
    ll liftdigit(ll node, ll k)
    {   
        ll num = 0;
        for (ll i = 0; i < LOG; i++)
        {
            if (k & (1 << i))
            {   
                num *= modPow(10, (1LL << (i)),MOD);
                num %= MOD;
                num += updigits[node][i];
                num %= MOD;
                node = up[node][i];
                if (node == -1)
                    break;
            }
        }
        return num;
    }

    ll liftdigitdown(ll node, ll k)
    {   
        ll num = 0;
        ll len = 0;
        for (ll i = 0; i < LOG; i++)
        {
            if (k & (1 << i))
            {   
                num += (modPow(10, len , MOD) * updigitsr[node][i])%MOD;
                num %= MOD;
                node = up[node][i];
                len += (1LL << i);
                if (node == -1)
                    break;
            }
        }
        return num;
    }

    // Time Complexity: O(LOG).
    // Returns: ll (The Lowest Common Ancestor node of a and b).
    // Description: get LCA in O(log(n)).
    ll LCA(ll a, ll b)
    {
        if (depth[a] < depth[b])
            swap(a, b);
            
        a = lift(a, depth[a] - depth[b]);
        
        if (a == b)
            return a;
            
        for (ll i = LOG - 1; i >= 0; i--)
        {
            if (up[a][i] != up[b][i])
            {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }
    ll depth1(ll x){
        return depth[x];
    }

    // Time Complexity: O(LOG) because it calls the LCA function.
    // Returns: ll (The number of edges / distance between node x and node y).
    // Description: Calculates the shortest path distance between two nodes on the tree.
    ll diff(ll x, ll y)
    {
        ll ans = depth[x] + depth[y] - 2 * depth[LCA(x, y)];
        return ans;
    }
};
using namespace std;
int main()
{
    HONDA
    int t = 1;
     cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q>>MOD;
        string ss;
        cin>>ss;
        s="0";
        s += ss;
        vector<vector<ll>> adj(n+1);
        fi(0,n-1){
            ll u,v;cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        lca_tree l(n+1, adj, 1);
        while(q--){
            ll x,y;cin>>x>>y;
            ll L = l.LCA(x,y);
            ll up=l.liftdigit(x, l.depth1(x) - l.depth1(L) + 1); 
            ll down=l.liftdigitdown(y, l.depth1(y) - l.depth1(L) );
            ll ans = ((up%MOD*modPow(10,  l.depth1(y) - l.depth1(L), MOD))%MOD + down%MOD)%MOD;
            cout << ans <<endl;
        }
        
        
        
    }
    return 0;
}