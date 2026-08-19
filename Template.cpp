#include <bits/stdc++.h>
using namespace std; typedef long long ll;

/////////////////// DSU //////////////////////////////////
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
        // parent[u] = root ;  // 3. Path compression make the function O(1)
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
//////////////////////////////////////////////////////////////

/////////////////// Small to Large //////////////////////////////////
{
    void merge(set<ll> & a, set<ll> & b)
    {
        if (a.size() < b.size())
        {
            swap(a, b);
        }
        for (ll x : b)
        {
            a.insert(x);
        }
    }
}
//////////////////////////////////////////////////////////////

///////////////////////fast exponentiation ///////////////////
{
    const int MAXN = 2e6;

    ll fact[MAXN + 1];
    ll invFact[MAXN + 1];

    ll power(ll base, ll exp)
    {
        ll res = 1;
        base %= MOD;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    ll modInverse(ll n)
    {
        return power(n, MOD - 2);
    }
    /*

    Vandermonde's Identity

    sumtion (i = 1 to k)[  [ k-1 C i-1 ] * [x , j] ]  ==  [ k+x+1 C  k ]

    Hockey-stick identity

    sumtion (i = x to k ) (i C x) == k+1 C n+1

    */
    void precompute()
    {
        fact[0] = 1;
        invFact[0] = 1;

        for (int i = 1; i <= MAXN; i++)
        {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        invFact[MAXN] = modInverse(fact[MAXN]);
        for (int i = MAXN - 1; i >= 1; i--)
        {
            invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
        }
    }

    ll C(int n, int r)
    {
        if (r < 0 || r > n || n > MAXN)
            return 0;
        ll num = fact[n];
        ll den = (invFact[r] * invFact[n - r]) % MOD;
        return (num * den) % MOD;
    }

    ll P(int n, int r)
    {
        if (r < 0 || r > n || n > MAXN)
            return 0;
        ll num = fact[n];
        ll den = invFact[n - r];
        return (num * den) % MOD;
    }

    ll small_r_C(ll n, ll r)
    {
        if (r < 0 || r > n)
            return 0;
        ll num = 1;
        ll den = 1;
        for (ll i = 1; i <= r; i++)
        {
            num = (num * ((n - i + 1) % MOD)) % MOD;
            den = (den * i) % MOD;
        }
        return (num * modInverse(den)) % MOD;
    }
}
////////////////////////////////////////////////////////////////////

///////////////////////////////////  sieve (Prime Sieve) //////////////////
{
    const ll N = 1e7 + 1;
    vector<bool> is_prime(N, true); //  Implements the Sieve of Eratosthenes to mark prime numbers
    void prime_sieve()              //  O(N log log N)
    {
        is_prime[0] = is_prime[1] = false;
        for (ll i = 2; i * i < N; i++)
        {
            if (is_prime[i])
            {
                for (ll j = i * i; j < N; j += i)
                {
                    is_prime[j] = false;
                }
            }
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////  sieve  ////////////////////////////////////////////////////////
{
    const ll N = 1e7 + 1;
    vector<ll> spf(N); ///////////   Computes the smallest prime factor  // O(N log log N)
    void sieve()
    {
        for (ll i = 0; i < N; i++)
            spf[i] = i;

        for (ll i = 2; i * i < N; i++)
        {
            if (spf[i] == i)
            {
                for (ll j = i * i; j < N; j += i)
                {
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }
    }

    vector<ll> get_factors(ll x) //    Returns the prime factors of a number  // O(log x) x limite to 1e7
    {
        vector<ll> factors;
        while (x != 1)
        {
            factors.push_back(spf[x]);
            x /= spf[x];
        }
        return factors;
    }

    vector<ll> get_factors(ll n)
    { //  Returns the prime factors of a number  // O(sqrt x) x limite to 1e14
        vector<ll> primes;
        for (ll d = 2; d * d <= n; d++)
        {
            if (n % d == 0)
            {
                primes.push_back(d);
                while (n % d == 0)
                    n /= d;
            }
        }
        if (n > 1)
            primes.push_back(n);
        return primes;
    }
}
///////////////////////////////////////////////////////////////////////////

//////////////////////////// LCA_tree ////////////////////////////////////////////////
{
    struct lca_tree
    {
    private:
        ll n;
        ll LOG = 20;
        vector<vector<ll>> adj;
        vector<vector<ll>> up;
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
}
/////////////////////////////////////////////////////////////////////////////

//////////////////////////// LCA_tree (with max/min edge on path) ////////////////////////////////////////////////
{
    struct lca_tree
    {
    private:
        ll n;
        ll LOG = 20;
        vector<vector<pair<ll, ll>>> adj; // {to, weight}
        vector<vector<ll>> up;
        vector<vector<ll>> up_max; // max edge weight in the 2^i jump from node
        vector<vector<ll>> up_min; // min edge weight in the 2^i jump from node
        vector<ll> depth;

        // Time Complexity: O(V * LOG)
        // Description: Precomputes 'up', 'up_max', 'up_min', and 'depth' via DFS.
        void dfs(ll node, ll parent, ll w)
        {
            up[node][0] = parent;
            up_max[node][0] = w; // w is weight of edge (parent -> node), 0 if root
            up_min[node][0] = w;

            for (ll i = 1; i < LOG; i++)
            {
                if (up[node][i - 1] != -1)
                {
                    up[node][i] = up[up[node][i - 1]][i - 1];
                    up_max[node][i] = max(up_max[node][i - 1], up_max[up[node][i - 1]][i - 1]);
                    up_min[node][i] = min(up_min[node][i - 1], up_min[up[node][i - 1]][i - 1]);
                }
                else
                {
                    up[node][i] = -1;
                    up_max[node][i] = up_max[node][i - 1];
                    up_min[node][i] = up_min[node][i - 1];
                }
            }

            for (auto &[to, wt] : adj[node])
            {
                if (to == parent)
                    continue;
                depth[to] = depth[node] + 1;
                dfs(to, node, wt);
            }
        }

    public:
        // Description: tree_adj[u] = list of {v, weight} for each edge u-v.
        lca_tree(ll nodes, vector<vector<pair<ll, ll>>> &tree_adj, ll root = 0)
        {
            n = nodes;
            adj = tree_adj;
            up = vector<vector<ll>>(n, vector<ll>(LOG, -1));
            up_max = vector<vector<ll>>(n, vector<ll>(LOG, LLONG_MIN));
            up_min = vector<vector<ll>>(n, vector<ll>(LOG, LLONG_MAX));
            depth = vector<ll>(n, 0);

            dfs(root, -1, 0);
        }

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

        ll diff(ll x, ll y)
        {
            ll ans = depth[x] + depth[y] - 2 * depth[LCA(x, y)];
            return ans;
        }

        // Time Complexity: O(LOG)
        // Returns: ll (maximum edge weight on the path from x to y).
        // Description: Walks x and y up to their LCA, tracking max edge weight passed.
        ll maxEdge(ll x, ll y)
        {
            ll l = LCA(x, y);
            ll ans = LLONG_MIN;

            auto climb = [&](ll node, ll target_depth)
            {
                ll k = depth[node] - target_depth;
                for (ll i = 0; i < LOG; i++)
                {
                    if (k & (1 << i))
                    {
                        ans = max(ans, up_max[node][i]);
                        node = up[node][i];
                    }
                }
            };

            climb(x, depth[l]);
            climb(y, depth[l]);

            return ans;
        }

        // Time Complexity: O(LOG)
        // Returns: ll (minimum edge weight on the path from x to y).
        // Description: Same idea as maxEdge but tracks minimum.
        ll minEdge(ll x, ll y)
        {
            ll l = LCA(x, y);
            ll ans = LLONG_MAX;

            auto climb = [&](ll node, ll target_depth)
            {
                ll k = depth[node] - target_depth;
                for (ll i = 0; i < LOG; i++)
                {
                    if (k & (1 << i))
                    {
                        ans = min(ans, up_min[node][i]);
                        node = up[node][i];
                    }
                }
            };

            climb(x, depth[l]);
            climb(y, depth[l]);

            return ans;
        }
    };
}
/////////////////////////////////////////////////////////////////////////////

//////////////////////////// LCA_tree (with path sum & path XOR) ////////////////////////////////////////////////
{
    struct lca_tree
    {
    private:
        ll n;
        ll LOG = 20;
        vector<vector<pair<ll, ll>>> adj; // {to, weight}
        vector<vector<ll>> up;
        vector<vector<ll>> up_sum; // sum of edge weights in the 2^i jump from node
        vector<vector<ll>> up_xor; // xor of edge weights in the 2^i jump from node
        vector<ll> depth;

        // Time Complexity: O(V * LOG)
        // Description: Precomputes 'up', 'up_sum', 'up_xor', and 'depth' via DFS.
        void dfs(ll node, ll parent, ll w)
        {
            up[node][0] = parent;
            up_sum[node][0] = w; // w is weight of edge (parent -> node), 0 if root
            up_xor[node][0] = w;

            for (ll i = 1; i < LOG; i++)
            {
                if (up[node][i - 1] != -1)
                {
                    up[node][i] = up[up[node][i - 1]][i - 1];
                    up_sum[node][i] = up_sum[node][i - 1] + up_sum[up[node][i - 1]][i - 1];
                    up_xor[node][i] = up_xor[node][i - 1] ^ up_xor[up[node][i - 1]][i - 1];
                }
                else
                {
                    up[node][i] = -1;
                    up_sum[node][i] = up_sum[node][i - 1];
                    up_xor[node][i] = up_xor[node][i - 1];
                }
            }

            for (auto &[to, wt] : adj[node])
            {
                if (to == parent)
                    continue;
                depth[to] = depth[node] + 1;
                dfs(to, node, wt);
            }
        }

    public:
        // Description: tree_adj[u] = list of {v, weight} for each edge u-v.
        lca_tree(ll nodes, vector<vector<pair<ll, ll>>> &tree_adj, ll root = 0)
        {
            n = nodes;
            adj = tree_adj;
            up = vector<vector<ll>>(n, vector<ll>(LOG, -1));
            up_sum = vector<vector<ll>>(n, vector<ll>(LOG, 0));
            up_xor = vector<vector<ll>>(n, vector<ll>(LOG, 0));
            depth = vector<ll>(n, 0);

            dfs(root, -1, 0);
        }

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

        ll diff(ll x, ll y)
        {
            ll ans = depth[x] + depth[y] - 2 * depth[LCA(x, y)];
            return ans;
        }

        // Time Complexity: O(LOG)
        // Returns: ll (sum of edge weights on the path from x to y).
        // Description: Walks x and y up to their LCA, accumulating edge weight sums.
        ll pathSum(ll x, ll y)
        {
            ll l = LCA(x, y);
            ll ans = 0;

            auto climb = [&](ll node, ll target_depth)
            {
                ll k = depth[node] - target_depth;
                for (ll i = 0; i < LOG; i++)
                {
                    if (k & (1 << i))
                    {
                        ans += up_sum[node][i];
                        node = up[node][i];
                    }
                }
            };

            climb(x, depth[l]);
            climb(y, depth[l]);

            return ans;
        }

        // Time Complexity: O(LOG)
        // Returns: ll (xor of edge weights on the path from x to y).
        // Description: Same idea as pathSum but accumulates with xor.
        ll pathXor(ll x, ll y)
        {
            ll l = LCA(x, y);
            ll ans = 0;

            auto climb = [&](ll node, ll target_depth)
            {
                ll k = depth[node] - target_depth;
                for (ll i = 0; i < LOG; i++)
                {
                    if (k & (1 << i))
                    {
                        ans ^= up_xor[node][i];
                        node = up[node][i];
                    }
                }
            };

            climb(x, depth[l]);
            climb(y, depth[l]);

            return ans;
        }
    };
}
/////////////////////////////////////////////////////////////////////////////


////////////////////////////SACK (DSU on trees)////////////////////////////////////////
{
    ll n; cin >> n;
    vector<vector<ll>> graph(n + 1);
    for(ll i = 0, u, v; i < n - 1; i++){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<ll> tin(n + 1), tout(n + 1), vertex(n + 1), sz(n + 1, 1), d(n + 1, 1);
    ll timer = 0;
    function<ll(ll, ll)> euler =[&](ll u, ll p){
        tin[u] = ++timer;
        vertex[tin[u]] = u;
        for(auto v : graph[u]) if(v != p){
            d[v] = d[u] + 1;
            sz[u] += euler(v, u);
        }
        tout[u] = timer;
        return sz[u];
    };
    euler(1, -1);

    auto add =[&](ll u){};
    auto remove =[&](ll u){};

    function<void(ll, ll, bool)> dfs =[&](ll u, ll p, bool keep){
        ll big = -1;
        for(auto v : graph[u]){
            if(v == p) continue;
            if(big == -1 || sz[v] > sz[big]) big = v;
        }
        for(auto v : graph[u]) 
            if(v != p && v != big) dfs(v, u, 0);
        if(big != -1) dfs(big, u, 1);
        for(auto v : graph[u]){
            if(v == p || v == big) continue;
            for(ll i = tin[v]; i <= tout[v]; i++){
                // here
                add(vertex[i]);
            }
        }
        add(u);
        if(!keep){
            for(ll i = tin[u]; i <= tout[u]; i++) remove(vertex[i]);
        }
    };
    dfs(1, -1, 1);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////Seg tree (point update)////////////////////////////////
{
    struct Node{
        ll mn;
        Node(){     //neutral node
            mn = 1e9;
        }
        Node(ll x){
            mn = x;
        }
        void change(ll x){
            mn = x;
        }
    };
    struct segtree{ //0-indexed [l,r)
        ll treesize;
        vector<Node> segdata;
        Node merge(Node &ln, Node &rn){
            Node ans = Node();
            ans.mn = min(ln.mn, rn.mn);
            return ans;
        }
        segtree(vector<ll> &arr){
            treesize = 1;
            while(treesize < arr.size()) treesize *= 2;
            segdata.assign(2*treesize, Node());
            for(ll i = 0; i < arr.size(); i++){
                segdata[treesize + i - 1] = Node(arr[i]);
            }
            for(ll i = treesize - 2; i >= 0; i--){
                segdata[i] = merge(segdata[2*i+1], segdata[2*i+2]);
            }
        }
        void update(ll ind, ll val, ll ni, ll lx, ll rx){
            if(rx - lx == 1){
                segdata[ni].change(val);
                return;
            }
            ll mid = (lx + rx)/2;
            if(ind < mid) update(ind, val, 2*ni+1, lx, mid);
            else update(ind, val, 2*ni+2, mid, rx);
            segdata[ni] = merge(segdata[2*ni+1], segdata[2*ni+2]);
        }
        Node get(ll l, ll r, ll ni, ll lx, ll rx){
            if(rx <= l || lx >= r) return Node();
            if(lx >= l && rx <= r) return segdata[ni];
            ll mid = (rx+lx)/2;
            Node ln = get(l, r, 2*ni+1, lx, mid);
            Node rn = get(l, r, 2*ni+2, mid, rx);
            return merge(ln, rn);
        }
    };
}
////////////////////////////////////////////////////////////////////////////////////////


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
////////////////////////Seg tree (merge sort tree, PBDS ordered set - updatable)////////////////////////////////
{
    typedef pair<ll,ll> pll; // (value, original_index) - index makes keys unique
    typedef tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update> ordset;

    // Summary table
    // Operation	                    Time Complexity	                    Why
    // Build (constructor)	            O(n log² n)	                    n leaves, each walks O(log n) ancestors, each ancestor insert is O(log(node size)) = O(log n)
    // update(ind, newVal)	            O(log² n)	                    walks O(log n) ancestors from leaf to root, each does one erase + one insert at O(log n) each
    // countLE(l, r, x)	                O(log² n)	                    touches O(log n) canonical nodes (standard seg-tree range decomposition), each does one order_of_key at O(log n)
    // countLT(l, r, x)	                O(log² n)	                    identical to countLE, just a different sentinel
    // kthSmallest(l, r, k, lo, hi)	    O(log(hi-lo) · log² n)	        binary search over the value range (O(log(value range)) iterations), each iteration calls countLE at O(log² n)
    
    // MemorySpace
    // Total across all nodes	O(n log n)

    struct Node{
        ordset vals;
        Node(){}    //neutral node (empty)
    };

    struct segtree{ //0-indexed [l,r)
        ll treesize;
        vector<Node> segdata;
        vector<ll> arr; // current value at each original index

        void insertAt(ll ni, ll val, ll idx){
            segdata[ni].vals.insert({val, idx});
        }
        void eraseAt(ll ni, ll val, ll idx){
            segdata[ni].vals.erase({val, idx});
        }

        segtree(vector<ll> &a){
            arr = a;
            treesize = 1;
            while(treesize < (ll)arr.size()) treesize *= 2;
            segdata.assign(2*treesize, Node());
            for(ll i = 0; i < (ll)arr.size(); i++){
                ll cur = treesize + i - 1;
                insertAt(cur, arr[i], i);
                while(cur != 0){
                    cur = (cur - 1) / 2;
                    insertAt(cur, arr[i], i);
                }
            }
        }

        // point update: set index ind to newVal, O(log^2 n)
        void update(ll ind, ll newVal){
            ll oldVal = arr[ind];
            if(oldVal == newVal) return;
            arr[ind] = newVal;
            ll cur = treesize + ind - 1;
            eraseAt(cur, oldVal, ind);
            insertAt(cur, newVal, ind);
            while(cur != 0){
                cur = (cur - 1) / 2;
                eraseAt(cur, oldVal, ind);
                insertAt(cur, newVal, ind);
            }
        }

        // count elements <= x in [l, r), O(log^2 n)
        ll countLE(ll l, ll r, ll x, ll ni, ll lx, ll rx){
            if(rx <= l || lx >= r) return 0;
            if(lx >= l && rx <= r){
                return segdata[ni].vals.order_of_key({x, (ll)4e18});   //change to -4e18 to count element < x in [l,r)
            }
            ll mid = (rx+lx)/2;
            return countLE(l, r, x, 2*ni+1, lx, mid) + countLE(l, r, x, 2*ni+2, mid, rx);
        }
        ll countLE(ll l, ll r, ll x){
            return countLE(l, r, x, 0, 0, treesize);
        }

        // k-th smallest (1-indexed) in [l, r), O(log n * log(value range)) via binary search on countLE
        ll kthSmallest(ll l, ll r, ll k, ll lo, ll hi){
            // [lo, hi] must bound all possible values
            while(lo < hi){
                ll mid = lo + (hi - lo) / 2;
                if(countLE(l, r, mid) >= k) hi = mid;
                else lo = mid + 1;
            }
            return lo;
        }
    };
}
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////Seg tree (bracket balance)////////////////////////////////
{
    struct Node{
        ll open, close; // unmatched '(' and ')' counts in this range
        Node(){     //neutral node
            open = 0;
            close = 0;
        }
        Node(char c){
            open = (c == '(') ? 1 : 0;
            close = (c == ')') ? 1 : 0;
        }
    };
    struct segtree{ //0-indexed [l,r)
        ll treesize;
        vector<Node> segdata;
        Node merge(Node &ln, Node &rn){
            Node ans = Node();
            ll cancel = min(ln.open, rn.close); // left's unmatched '(' pair with right's unmatched ')'
            ans.open  = (ln.open - cancel) + rn.open;
            ans.close = (rn.close - cancel) + ln.close;
            return ans;
        }
        segtree(vector<char> &arr){
            treesize = 1;
            while(treesize < arr.size()) treesize *= 2;
            segdata.assign(2*treesize, Node());
            for(ll i = 0; i < arr.size(); i++){
                segdata[treesize + i - 1] = Node(arr[i]);
            }
            for(ll i = treesize - 2; i >= 0; i--){
                segdata[i] = merge(segdata[2*i+1], segdata[2*i+2]);
            }
        }
        void update(ll ind, char val, ll ni, ll lx, ll rx){
            if(rx - lx == 1){
                segdata[ni] = Node(val);
                return;
            }
            ll mid = (lx + rx)/2;
            if(ind < mid) update(ind, val, 2*ni+1, lx, mid);
            else update(ind, val, 2*ni+2, mid, rx);
            segdata[ni] = merge(segdata[2*ni+1], segdata[2*ni+2]);
        }
        Node get(ll l, ll r, ll ni, ll lx, ll rx){
            if(rx <= l || lx >= r) return Node();
            if(lx >= l && rx <= r) return segdata[ni];
            ll mid = (rx+lx)/2;
            Node ln = get(l, r, 2*ni+1, lx, mid);
            Node rn = get(l, r, 2*ni+2, mid, rx);
            return merge(ln, rn);
        }
    };
}
//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////Seg tree (range update)///////////////////////////////////
{
    struct Node{
        ll mx;
        ll lazy=0;
        bool islazy = 0;
        Node(){     //neutral node
            mx = 0;
        }
        Node(ll x){ 
            mx = x;
        }
        void update(ll x,ll lx, ll rx){
            mx += x;
            lazy += x;
            islazy = 1;
        }
    };
    struct segtree{
        ll treesize;
        vector<Node> segdata;
        Node merge(Node &ln, Node &rn){
            Node ans = Node();
            ans.mx = max(ln.mx , rn.mx);
            return ans;
        }
        segtree(vector<ll> &arr){
            treesize = 1;
            while(treesize < arr.size()) treesize *= 2;
            segdata.assign(2*treesize, Node());
            for(ll i = 0; i < arr.size(); i++){
                segdata[treesize + i - 1] = Node(arr[i]);
            }
            for(ll i = treesize - 2; i >= 0; i--){
                segdata[i] = merge(segdata[2*i+1], segdata[2*i+2]);
            }
        }
        void propagate(ll ni, ll lx, ll rx){
            if(rx-lx==1 || !segdata[ni].islazy) return;
            ll mid = (lx + rx)/2;
            segdata[2*ni+1].update(segdata[ni].lazy,lx,mid);
            segdata[2*ni+2].update(segdata[ni].lazy,mid,rx);
            segdata[ni].lazy = segdata[ni].islazy = 0;
        }
        void update_range(ll l,ll r, ll val,ll ni, ll lx, ll rx){
            propagate(ni, lx, rx);
            if(rx <= l || lx >= r) return;
            if(lx >= l && rx <= r){
                segdata[ni].update(val, lx, rx);
                return;
            }
            ll mid = (rx + lx)/2;
            update_range(l, r, val, 2*ni+1, lx, mid);
            update_range(l, r, val, 2*ni+2, mid, rx);
            segdata[ni] = merge(segdata[2*ni+1], segdata[2*ni+2]);
        }
        ll get(ll num,ll ind, ll ni, ll lx, ll rx){
            propagate(ni, lx, rx);
            if(segdata[ni].mx < num || ind >= rx) return -1;
            if(rx - lx == 1) return lx;
            ll mid = (lx + rx)/2;
            ll left = get(num, ind, 2*ni+1, lx, mid);
            if(left != -1) return left;
            else return get(num, ind, 2*ni+2, mid, rx);
        }
    };
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////FFT///////////////////////////////////////////////////
{
    using cd = complex<double>;
    const double PI = acos(-1);

    void fft(vector<cd> & a, bool invert) {
        int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd & x : a)
                x /= n;
        }
    }

    vector<int> multiply(vector<int> const& a, vector<int> const& b) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < (ll)a.size() + (ll)b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<int> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());
        return result;
    }
}
///////////////////////////////////////////////////////////////////////////////

////////////////////////FFT (p1*p2, P^k, muliply 2 big int, big int ^ k)///////////////////////////////////////////////
{
    void fft(vector<cd> & a, bool invert) {
        ll n = a.size();

        for (ll i = 1, j = 0; i < n; i++) {
            ll bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (ll len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (ll i = 0; i < n; i += len) {
                cd w(1);
                for (ll j = 0; j < len / 2; j++) {
                    cd u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd & x : a)
                x /= n;
        }
    }

    vector<ll> multiply(vector<ll> const& a, vector<ll> const& b, ll limit) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        ll n = 1;
        while (n < (ll)a.size() + (ll)b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (ll i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<ll> result(min(n,limit));
        for (ll i = 0; i < min(n,limit); i++)
            result[i] = round(fa[i].real());
        return result;
    }
    vector<ll> poly_pow(vector<ll> p, ll k){
        vector<ll> ans{1};
        while(k){
            if(k&1) ans = multiply(ans, p, 1e6);
            p = multiply(p, p, 1e6);
            k>>=1;
        }
        return ans;
    }
    string mul_two_big_int(const string &s1, const string &s2) {
        ll n = s1.size(), m = s2.size();

        vector<ll> poly1(n), poly2(m);
        for (ll i = 0; i < n; ++i) {
            poly1[n-i-1] = s1[i] - '0';
        }

        for (ll i = 0; i < m; ++i) {
            poly2[m-i-1] = s2[i] - '0';
        }

        vector<ll> ans = multiply(poly1, poly2);
        ll k = ans.size();

        for (ll i = 0; i < k - 1; ++i) {
            ans[i + 1] += ans[i] / 10;
            ans[i] = ans[i] % 10;
        }

        string final = to_string(ans[k - 1]);
        for (ll i = k - 2; i >= 0; --i) {
            final += (char)(ans[i] + '0');
        }

        for (ll i = 0; i < k; ++i) {
            if(final[i] != '0') return final.substr(i);
        }
        return "0";
    }

    string power_of_big_int(string s, ll p) {
        string ans = "1";
        while (p) {
            if(p&1) ans = mul_two_big_int(ans, s);
            s = mul_two_big_int(s, s);
            p >>= 1;
        }
        return ans;
    }
}
//////////////////////////////////////////////////////////////////////////////

////////////////////FFT with MOD////////////////////////////////////////////
{
    #define rep(aa, bb, cc) for(int aa = bb; aa < cc;aa++)
    #define sz(a) (int)a.size()
    typedef complex<double> C;
    typedef vector<double> vd;
    void fft(vector<C>& a) {
        int n = sz(a), L = 31 - __builtin_clz(n);
        static vector<complex<long double>> R(2, 1);
        static vector<C> rt(2, 1);  // (^ 10% faster if double)
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n); rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
        }
        vi rev(n);
        rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
                    // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                    auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
                    C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
    }
    
    template<int M> vi convMod(const vi &a, const vi &b) {
        if (a.empty() || b.empty()) return {};
        vi res(sz(a) + sz(b) - 1);
        int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
        vector<C> L(n), R(n), outs(n), outl(n);
        rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
        rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
        fft(L), fft(R);
        rep(i,0,n) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl), fft(outs);
        rep(i,0,sz(res)) {
            ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
            ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
            res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
        }
        return res;
    }
}
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////NTT/////////////////////////////////////
{
    const ll mod = (119 << 23) + 1, root = 62; // = 998244353
    // For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
    // and 483 << 21 (same root). The last two are > 10^9.


    ll modpow(ll b, ll e) {
        ll ans = 1;
        for (; e; b = b * b % mod, e /= 2)
            if (e & 1) ans = ans * b % mod;
        return ans;
    }

    // Primitive Root of the mod of form 2^a * b + 1
    int generator () {
        vector<int> fact;
        int phi = mod-1,  n = phi;
        for (int i=2; i*i<=n; ++i)
            if (n % i == 0) {
                fact.push_back (i);
                while (n % i == 0)
                    n /= i;
            }
        if (n > 1)
            fact.push_back (n);

        for (int res=2; res<=mod; ++res) {
            bool ok = true;
            for (size_t i=0; i<fact.size() && ok; ++i)
                ok &= modpow (res, phi / fact[i]) != 1;
            if (ok)  return res;
        }
        return -1;
    }
    int modpow(int b, int e, int m) {
        int ans = 1;
        for (; e; b = (ll)b * b % m, e /= 2)
            if (e & 1) ans = (ll)ans * b % m;
        return ans;
    }

    void ntt(vector<int> &a) {
        int n = (int)a.size(), L = 31 - __builtin_clz(n);
        vector<int> rt(2, 1); // erase the static if you want to use two moduli;
        for (int k = 2, s = 2; k < n; k *= 2, s++) { // erase the static if you want to use two moduli;
            rt.resize(n);
            int z[] = {1, modpow(root, mod >> s, mod)};
            for (int i = k; i < 2*k; ++i) rt[i] = (ll)rt[i / 2] * z[i & 1] % mod;
        }
        vector<int> rev(n);
        for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; ++j) {
                    int z = (ll)rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                    a[i + j + k] = ai - z + (z > ai ? mod : 0);
                    ai += (ai + z >= mod ? z - mod : z);
                }
            }
        }
    }
    vector<int> conv(const vector<int> &a, const vector<int> &b) {
        if (a.empty() || b.empty()) return {};
        int s = (int)a.size() + (int)b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
        int inv = modpow(n, mod - 2, mod);
        vector<int> L(a), R(b), out(n);
        L.resize(n), R.resize(n);
        ntt(L), ntt(R);
        for (int i = 0; i < n; ++i) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
        ntt(out);
        return {out.begin(), out.begin() + s};
    }

    ll CRT(ll a, ll m1, ll b, ll m2) {
        __int128 m = m1*m2;
        ll ans = a*m2%m*modpow(m2, m1-2, m1)%m + m1*b%m*modpow(m1, m2-2, m2)%m;
        return ans % m;
    }


    /*

    int mod, root, desired_mod = 1000000007;
    const int mod1 = 167772161;
    const int mod2 = 469762049;
    const int mod3 = 754974721;
    const int root1 = 3;
    const int root2 = 3;
    const int root3 = 11;

    int CRT(int a, int b, int c, int m1, int m2, int m3) {
        __int128 M = (__int128)m1*m2*m3;
        ll M1 = (ll)m2*m3;
        ll M2 = (ll)m1*m3;
        ll M3 = (ll)m2*m1;

        int M_1 = modpow(M1%m1, m1 - 2, m1);
        int M_2 = modpow(M2%m2, m2 - 2, m2);
        int M_3 = modpow(M3%m3, m3 - 2, m3);

        __int128 ans = (__int128)a*M1*M_1;
        ans += (__int128)b*M2*M_2;
        ans += (__int128)c*M3*M_3;

        return (ans % M) % desired_mod;
    }

    */
}
//////////////////////////////////////////////////////////////////////////////