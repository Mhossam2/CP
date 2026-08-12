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
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vector<vector<ll>> adj(n+1);
        vector<ll> depth(n + 1,0);
        fi(0,n-1){
            ll u,v;cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }  
        auto dfs = [&](auto &&self,ll node,ll parent) -> void
        {
            for(ll ch:adj[node]){
                if(ch==parent) continue;
                depth[ch]=depth[node]+1;
                self(self, ch, node);
            }
        };
        dfs(dfs,1,0);
        ll d1=0;
        fi(1,n+1){
            if(depth[i]>depth[d1]){
                d1 = i;
            }
        }
        fi(0,n + 1) depth[i]=0;
        dfs(dfs,d1,0);
        vector<ll> dist(n + 1,0);
        ll d2=0;
        fi(0,n+1){
            if(depth[i]>depth[d2]){
                d2 = i;
            }
            dist[i] = depth[i];
        }
        fi(0,n + 1) depth[i] = 0;
        dfs(dfs, d2, 0);
        vector<ll> a(n,0);
        fi(0,n+1){
            dist[i]= max(dist[i],depth[i]);
            a[dist[i]]++;
        }
        for(ll i=n-1;i>=0;i--){
            if(a[i]){
                a[i]--;
                break;
            }
        }
        for(ll i = n-2;i>=0;i--){
            a[i] += a[i+1];
        }
        fi(1,n) cout<<n - a[i]<<" ";
        cout<<n;

    }
    return 0;
}
