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
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,m;cin>>n>>m;
        vector<Edge> edges(m);
        fi(0,m){
            cin>>edges[i].u>>edges[i].v>>edges[i].w;
            edges[i].u--;
            edges[i].v--;
            edges[i].ind == i;

        }
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.w < b.w;
        });
        vector<ll> ans(m);
        fi(0,m){
            DSU dsu(n);
            ll total = edges[i].w;
            dsu.merge(edges[i].u, edges[i].v);
            ll used = 1;
            fj(0,m){
                if(edges[j].ind == i) continue;
                if(dsu.find_root(edges[j].u) != dsu.find_root(edges[j].v)){
                    total += edges[j].w;
                    dsu.merge(edges[j].u, edges[j].v);
                    used++;
                    if(used == n-1) break;
                }
            }
            ans[edges[i].ind] = total;
        }
        fi(0,m) cout<<ans[i]<<endl;

    }
    return 0;
}
