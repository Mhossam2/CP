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
struct DSU{
    vector<ll> parent, size;
    DSU(ll n){
        parent.resize(n);
        size.resize(n+1);
        for(ll i=0; i<n; i++) parent[i]=i;
    }
    ll find_set(ll v) {  //find the leader of the set in very small constant of time
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(ll a, ll b) { //merge two sets O(1)
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};
void dfs(ll node, ll parent, vector<vector<ll>> &adj, vector<ll> &color, vector<set<ll>> &ans){
    ans[node].insert(color[node]);
    for(ll nxt: adj[node]){
        if(nxt == parent) continue;
        ans[node].insert(color[nxt]);
        dfs(nxt,node,adj,color,ans);
    }
}
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vll color(n+1);
        fi(1,n+1){
            cin>>color[i];
        }  
        vector<vector<ll>> adj(n+1);
        fi(0,n-1){
            ll x,y;cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vector<set<ll>> ans(n);
    }
    return 0;
}
