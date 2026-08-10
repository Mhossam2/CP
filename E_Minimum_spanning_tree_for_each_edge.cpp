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
struct DSU
{
    vector<ll> parent, sizes, depth;
    DSU(ll n)
    {
        parent.resize(n + 1);
        sizes.resize(n + 1, 1);
        depth.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    ll find_root(ll u)
    {
        if (parent[u] == u)
            return u;
        ll root = find_root(parent[u]);
        depth[u] += depth[parent[u]];
        parent[u] = root ;  // 3. Path compression make the function O(1)
        return root;
    }
    bool merge(ll u, ll v)
    {
        ll root_u = find_root(u);
        ll root_v = find_root(v);

        if (root_u == root_v)
            return 0; // oredy in the same set

        if (sizes[root_v] < sizes[root_u])
            swap(root_u, root_v);

        sizes[root_v] += sizes[root_u];
        parent[root_u] = root_v;
        depth[root_u] = 1;

        return 1;
    }
};
struct Edge{
    ll w,ind,u,v;
};
struct lca_tree
    {
    private:
        ll n;
        ll LOG = 20;
        vector<vector<pair<ll,ll>>> adj;
        vector<vector<ll>> up;
        vector<vector<ll>> mx;

        // Time Complexity: O(V * LOG) where V is the number of vertices.
        // Returns: void.
        // Description: Precomputes the 'up' table for binary lifting and calculates the 'depth' of each node.
        void dfs(ll node, ll parent, ll w)
        {
            up[node][0] = parent;
            mx[node][0] = w;
            for (ll i = 1; i < LOG; i++)
            {
                if (up[node][i - 1] != -1){
                    up[node][i] = up[up[node][i - 1]][i - 1];
                    mx[node][i] = max(mx[up[node][i-1]][i-1], mx[node][i - 1]);
                }
                else
                    up[node][i] = -1;
            }
            for (ll i = 0; i < adj[node].size(); i++)
            {
                auto [to,w] = adj[node][i];
                if (to == parent)
                {
                    continue;
                }
                depth[to] = depth[node] + 1;
                dfs(to, node, w);
            }
        }
    public:
        vector<ll> depth;
        // Time Complexity: O(V * LOG) for the initial build.
        // Returns: Constructor (No return type).
        // Description: Initializes the tree sizes, arrays, and starts the DFS from the root.
        lca_tree(ll nodes, vector<vector<pair<ll,ll>>> &tree_adj, ll root = 0)
        {
            n = nodes;
            adj = tree_adj;
            up = vector<vector<ll>>(n, vector<ll>(LOG, -1));
            depth = vector<ll>(n, 0);
            mx = vector<vector<ll>> (n,vector<ll> (LOG, 0));

            // depth of root is 0, parent of root is -1
            dfs(root, -1, 0);
        }

        // Time Complexity: O(LOG).
        // Returns: ll (The k-th ancestor of the given node, or -1 if the ancestor doesn't exist).
        // Description: get kth ancestor using binary lifting.
        pair<ll,ll> lift(ll node, ll k)
        {
            ll ans = 0;
            for (ll i = 0; i < LOG; i++)
            {
                if (k & (1 << i))
                {
                    ll nxt = up[node][i];
                    if (nxt == -1)
                        break;
                    ans = max(ans, mx[node][i]);
                    node = nxt;
                }
            }
            return {ans,node};
        }

        // Time Complexity: O(LOG).
        // Returns: ll (The Lowest Common Ancestor node of a and b).
        // Description: get LCA in O(log(n)).
        ll LCA(ll a, ll b)
        {
            if (depth[a] < depth[b])
                swap(a, b);
            a = lift(a, depth[a] - depth[b]).second;

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

        // Time Complexity: O(LOG) because it calls the LCA function.
        // Returns: ll (The number of edges / distance between node x and node y).
        // Description: Calculates the shortest path distance between two nodes on the tree.
        ll diff(ll x, ll y)
        {
            ll ans = depth[x] + depth[y] - 2 * depth[LCA(x, y)];
            return ans;
        }
    };
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,m;cin>>n>>m;
        vector<Edge> edges(m);
        vector<vector<pair<ll,ll>>> adj(n);
        fi(0,m){
            cin>>edges[i].u>>edges[i].v>>edges[i].w;
            edges[i].u--;
            edges[i].v--;
            edges[i].ind = i;
        }
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });
        vector<ll> ans(m);
        vector<ll> vis(m,0);
        DSU dsu(n);
        ll total = 0;
        ll used = 0;
        fi(0,m){
            if(dsu.find_root(edges[i].u) != dsu.find_root(edges[i].v)){
                total += edges[i].w;
                dsu.merge(edges[i].u, edges[i].v);
                used++;
                vis[edges[i].ind]=1;
                if(used == n-1) break;
            }
        }
        fi(0,m){
            if(vis[edges[i].ind]){
                adj[edges[i].u].push_back({edges[i].v,edges[i].w});
                adj[edges[i].v].push_back({edges[i].u,edges[i].w});
            }
        }
        lca_tree lca(n, adj, 0);
        fi(0,m){
            if(vis[edges[i].ind]) ans[edges[i].ind]=total;
            else{
                ll lc = lca.LCA(edges[i].u,edges[i].v);
                ll mx = max(lca.lift(edges[i].u,abs(lca.depth[lc]-lca.depth[edges[i].u])).first,lca.lift(edges[i].v,abs(lca.depth[lc]-lca.depth[edges[i].v])).first);
                ans[edges[i].ind] = total - mx + edges[i].w;
            }
        }
        fi(0,m) cout<<ans[i]<<endl;
    }
    return 0;
}
