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
        ll n,m,s,t;cin>>n>>m>>s>>t;
        vector<vector<ll>> adj(n+1);
        vector<vector<ll>> occ(n+1, vector<ll> (n+1,false));
        fi(0,m){
            ll u,v;cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            occ[u][v]=occ[v][u]=true;
        }
        auto bfs = [&](ll root){
            vector<ll> dist(n+1,1e18);
            queue<ll> q;
            dist[root] = 0;
            q.push(root);
            while(!q.empty()){
                ll cur = q.front(); q.pop();
                for(ll nxt:adj[cur]){
                    if(dist[nxt]>dist[cur]+1){
                        dist[nxt]=dist[cur]+1;
                        q.push(nxt);
                    }
                }
            }
            return dist;
        };
        vector<ll> sd = bfs(s);
        vector<ll> td = bfs(t);
        ll ans=0;
        fi(1,n+1){
            fj(i+1,n+1){
                if(!occ[i][j]){
                    if(min(sd[i]+td[j]+1,sd[j]+td[i]+1)>=sd[t]) ans++;
                }
            }
        }
        cout<<ans;
    }
    return 0;
}
