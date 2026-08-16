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
void dfs(ll u,ll p){
    
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n,k;cin>>n>>k;
        vll a(n);
        map<ll,vector<ll>> mp;
        fi(0,n){
            cin>>a[i];
            mp[a[i]].push_back(i);
        }
        vector<vector<ll>> adj(n);
        for(ll i =0;i<n-1;i++){
            ll u,v;cin>>u>>v;
            u--;v--;
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
        vector<ll> subtree(n,0);
        auto dfs = [&](auto &&self,ll u,ll p) ->void
        {
            subtree[u]=1;
            for(ll v:adj[u]){
                if(v==p) continue;
                self(self,v,u);
                subtree[u]+=subtree[v];
            }
        };
        dfs(dfs,0,-1);
        ll ans = 0;
        vector<pair<ll,ll>> b(n);
        for(ll i =0;i<n;i++){
            b[i]={a[i],i};
        }
        sort(all(b));
        for(ll i=0;i<n;i++){
            for(ll j=0;j<mp[k*b[i].first].size();j++){
                ans += subtree[b[i].second] * subtree[mp[k*b[i].first][j]]; 
            }
        }
        cout<<ans;
    }
    return 0;
}
