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
const ll MOD = 1e9+7;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        vll w(n+1);
        vll a(n+1);
        for(ll i=1;i<n+1;i++){
            cin>>a[i];
        } 
        for(ll i=1;i<=n;i++){
            cin>>w[i];
        }
        vector<vector<ll>> adj(n+1);
        for(ll i=0;i<n-1;i++){
            ll x,y;cin>>x>>y;
            adj[y].push_back(x);
            adj[x].push_back(y);
        }
        vector<ll> dis,In(n+1),Out(n+1);
        auto dfs = [&](auto &&self,ll node, ll parent) -> void
        {
            dis.push_back(node);
            In[node]=dis.size();
            for(ll ch:adj[node]){
                if(ch==parent) continue;
                self(self,ch,node);
            }
            Out[node]=dis.size();
        };
        dfs(dfs,1,0);
        
    }
    return 0;
}
