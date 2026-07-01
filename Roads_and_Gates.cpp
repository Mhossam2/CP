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
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,m,y;cin>>n>>m>>y;
        ll v = n+1;
        vector<vector<pair<ll,ll>>> adj(n+2);
        fi(0,m){
            ll u,v,c;cin>>u>>v>>c;
            adj[u].push_back({c,v});
            adj[v].push_back({c,u});
        }
        vll x(n+1);
        fi(1,n+1) cin>>x[i];
        fi(1,n+1){
            adj[i].push_back({x[i],v});
            adj[v].push_back({x[i]+y, i});
        }
        vector<ll> dist(n + 2, 1e18);
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
        dist[1] = 0;
        pq.push({0, 1});
        
        while(!pq.empty()){
            auto [d, u] = pq.top(); pq.pop();
            if(d > dist[u]) continue;
            for(auto &[w, v] : adj[u]){
                if(dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        for(ll k = 2; k <= n; k++){
            cout << dist[k];
            if(k < n) cout << " ";
        }
    }
    return 0;
}
