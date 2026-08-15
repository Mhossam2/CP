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
///////////////////////  Segment Tree (Point Update Range Query) //////////////////////
struct segment_tree
{
private:
    ll sz;
    vector<ll> seg;

#define L 2 * node + 1
#define R 2 * node + 2
#define mid ((l + r) >> 1)

    ll base = 1e18; // the value doesn't effect on the segment tree  __ according to it's type

    ll merge(ll x, ll y)
    { /////////////  type of seg  depend on (base value and merge )
        return min(x, y);
    }
    void build(ll l, ll r, ll node, vector<ll> &arr)
    {

        if (l == r)
        {
            if (l < arr.size())
            {
                seg[node] = arr[l];
            }
            return;
        }
        build(l, mid, L, arr);     // left
        build(mid + 1, r, R, arr); // right

        seg[node] = merge(seg[L], seg[R]);
    }

    void update(ll l, ll r, ll node, ll idx, ll val)
    {
        if (l == r)
        {
            seg[node] = val;
            return;
        }

        if (idx <= mid)
        {
            update(l, mid, L, idx, val); // left
        }
        else
        {
            update(mid + 1, r, R, idx, val); // right
        }
        seg[node] = merge(seg[L], seg[R]);
    }

    ll query(ll l, ll r, ll node, ll lq, ll rq)
    {

        if (r < lq || l > rq)
            return base;

        if (lq <= l && rq >= r)
            return seg[node];

        ll left = query(l, mid, L, lq, rq); // left

        ll right = query(mid + 1, r, R, lq, rq); // right

        return merge(left, right);
    }

public:
    segment_tree(vector<ll> &arr)
    {
        sz = 1;
        ll n = arr.size();
        while (sz < n)
            sz *= 2;

        seg = vector<ll>(sz * 2, base);

        build(0, sz - 1, 0, arr);
    }

    void update(ll idx, ll val)
    {
        update(0, sz - 1, 0, idx, val);
    }

    ll query(ll l, ll r)
    {
        return query(0, sz - 1, 0, l, r);
    }

#undef R
#undef L
#undef mid
};
///////////////////////////////////////////////////////////////////////////////////////
const ll MOD = 1e9+7;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
    ll n,q; cin >> n>>q;
    vector<vector<pair<ll,ll>>> asks(n+1);
    fi(0,)
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
    return 0;
}
