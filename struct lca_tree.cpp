struct lca_tree
{
private:
    ll n;
    ll LOG = 20;
    vector<vector<ll>> adj;
    vector<vector<ll>> up;
    vector<vector<ll>> updigits;
    vector<ll> depth;

    // Time Complexity: O(V * LOG) where V is the number of vertices.
    // Returns: void.
    // Description: Precomputes the 'up' table for binary lifting and calculates the 'depth' of each node.
    void dfs(ll node, ll parent)
    {
        up[node][0] = parent;
        for (ll i = 1; i < LOG; i++)
        {
            if (up[node][i - 1] != -1)
                up[node][i] = up[up[node][i - 1]][i - 1];
                updigits[node][i] = (updigits[node][i-1])*pow(10,i-1) + updigits[updigits[node][i-1]][i-1];
            else
                up[node][i] = -1;
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
    lca_tree(ll nodes, vector<vector<ll>> &tree_adj, ll root = 0)
    {
        n = nodes;
        adj = tree_adj;
        up = vector<vector<ll>>(n, vector<ll>(LOG, -1));
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

    // Time Complexity: O(LOG) because it calls the LCA function.
    // Returns: ll (The number of edges / distance between node x and node y).
    // Description: Calculates the shortest path distance between two nodes on the tree.
    ll diff(ll x, ll y)
    {
        ll ans = depth[x] + depth[y] - 2 * depth[LCA(x, y)];
        return ans;
    }
};