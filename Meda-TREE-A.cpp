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
        vll color(n);
        fi(0,n){
            cin>>color[i];
        }  
        vector<vector<ll>> adj(n);
        fi(0,n-1){
            ll x,y;cin>>x>>y;
            x--;y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vector<set<ll>> ans(n);
        dfs(0,-1,adj,color,ans);
        fi(0,n){
            cout<<ans[i].size()<<" ";
        }
    }
    return 0;
}
