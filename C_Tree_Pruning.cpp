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
ll dfs(ll node,ll parent, vector<vector<ll>> &adj, vector<ll> &depth,vector<ll> &hight){
    for(ll nxt : adj[node]){
        if(nxt==parent) continue;
        depth[nxt]=depth[node]+1;
        dfs(nxt,node,adj,depth,hight);
        hight[node] = max(hight[nxt],hight[node]) + 1;
    }
}
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vector<vector<ll>> adj(n);
        fi(0,n-1){
            ll u,v;cin>>u>>v;
            u--;v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<ll> depth(n,0);
        vll hight(n,0);
        vector<ll> ranges(n,0);
        dfs(0, -1,adj,depth,hight);
        fi(0,n){
            ranges[depth[i]]++;
            ranges[depth[i]+hight[i]]--;
        }
        fi(1,n){
            ranges[i]= ranges[i]+ranges[i-1];
        }
        ll ans = 0;
        fi(0,n){
            ans=max(ans,ranges[i]);
        }
        cout<<n-ans<<endl;
    }
    return 0;
}
