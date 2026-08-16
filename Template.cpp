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

