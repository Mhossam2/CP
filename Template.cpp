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
{
    int n; cin >> n;
    vector<vector<int>> graph(n + 1);
    for(int i = 0, u, v; i < n - 1; i++){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> tin(n + 1), tout(n + 1), vertex(n + 1), sz(n + 1, 1), d(n + 1, 1);
    int timer = 0;
    function<int(int, int)> euler =[&](int u, int p){
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

    auto add =[&](int u){};
    auto remove =[&](int u){};

    function<void(int, int, bool)> dfs =[&](int u, int p, bool keep){
        int big = -1;
        for(auto v : graph[u]){
            if(v == p) continue;
            if(big == -1 || sz[v] > sz[big]) big = v;
        }
        for(auto v : graph[u]) 
            if(v != p && v != big) dfs(v, u, 0);
        if(big != -1) dfs(big, u, 1);
        for(auto v : graph[u]){
            if(v == p || v == big) continue;
            for(int i = tin[v]; i <= tout[v]; i++){
                // here
                add(vertex[i]);
            }
        }
        add(u);
        if(!keep){
            for(int i = tin[u]; i <= tout[u]; i++) remove(vertex[i]);
        }
    };
    dfs(1, -1, 1);
}
