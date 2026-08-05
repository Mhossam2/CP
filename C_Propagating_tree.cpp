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
struct Node
{
    ll sm;
    Node()
    { // neutral node
        sm = 0;
    }
    Node(ll x)
    {
        sm = x;
    }
    void change(ll x)
    {
        sm += x;
    }
};
struct segtree
{ // 0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln, Node &rn)
    {
        Node ans = Node();
        ans.sm = ln.sm + rn.sm;
        return ans;
    }
    segtree(vector<ll> &arr)
    {
        treesize = 1;
        while (treesize < arr.size())
            treesize *= 2;
        segdata.assign(2 * treesize, Node());
        for (ll i = 0; i < arr.size(); i++)
        {
            segdata[treesize + i - 1] = Node(arr[i]);
        }
        for (ll i = treesize - 2; i >= 0; --i)
        {
            segdata[i] = merge(segdata[2 * i + 1], segdata[2 * i + 2]);
        }
    }
    void update(ll ind, ll val, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            segdata[ni].change(val);
            return;
        }
        ll mid = (lx + rx) / 2;
        if (ind < mid)
            update(ind, val, 2 * ni + 1, lx, mid);
        else
            update(ind, val, 2 * ni + 2, mid, rx);
        segdata[ni] = merge(segdata[2 * ni + 1], segdata[2 * ni + 2]);
    }
    Node get(ll l, ll r, ll ni, ll lx, ll rx)
    {
        if (rx <= l || lx >= r)
            return Node();
        if (lx >= l && rx <= r)
            return segdata[ni];
        ll mid = (rx + lx) / 2;
        Node ln = get(l, r, 2 * ni + 1, lx, mid);
        Node rn = get(l, r, 2 * ni + 2, mid, rx);
        return merge(ln, rn);
    }
};
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<ll> &discover, vector<ll> &begin, vector<ll> &finish, vector<ll> &depth)
{
    discover.push_back(node);
    begin[node] = discover.size();
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        depth[nxt] = depth[node] + 1;
        dfs(nxt, node, adj, discover, begin, finish, depth);
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
        ll n, q;
        cin >> n >> q;
        vll a(n);
        fi(0, n) cin >> a[i];
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
        vector<ll> depth(n, 0), begin(n), finish(n), discover;
        dfs(0, 0, adj, discover, begin, finish, depth);
        vll ev(n + 2, 0), od(n + 2, 0);
        segtree segev = segtree(ev);
        segtree segod = segtree(od);
        while (q--)
        {
            ll type, node;
            cin >> type >> node;
            node--;
            if (type == 1)
            {
                ll val;
                cin >> val;
                if (depth[node] % 2 == 0)
                {
                    segev.update(begin[node], val, 0, 0, segev.treesize);
                    segev.update(finish[node] + 1, -val, 0, 0, segev.treesize);
                    segod.update(begin[node], -val, 0, 0, segev.treesize);
                    segod.update(finish[node] + 1, val, 0, 0, segev.treesize);
                }
                else
                {
                    segod.update(begin[node], val, 0, 0, segev.treesize);
                    segod.update(finish[node] + 1, -val, 0, 0, segev.treesize);
                    segev.update(begin[node], -val, 0, 0, segev.treesize);
                    segev.update(finish[node] + 1, val, 0, 0, segev.treesize);
                }
            }
            else
            {
                ll num;
                if (depth[node] % 2 == 0)
                {
                    num = segev.get(0, begin[node], 0 ,0,segev.treesize).sm;
                }
                else{
                    num = segod.get(0, begin[node], 0 ,0,segev.treesize).sm;
                }
                cout<<a[node]+num<<endl;
            }
        }
    }
    return 0;
}
