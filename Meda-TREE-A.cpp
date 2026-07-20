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
        vector<ll> p(n+1,0);
        vector<ll> path;
        vector<bool> vis(n+1,false);
        queue<ll> q;
        q.push(1);
        vis[1]=1;
        while(!q.empty()){
            ll node = q.front(); q.pop();
            path.push_back(node);
            for(ll nxt : adj[node]){
                if(vis[nxt]) continue;
                vis[nxt] = 1;
                p[nxt] = node;
                q.push(nxt);
            }
        }
        vector<vector<ll>> c(n+1);
        for(ll u: path){
            if(u!=1) c[p[u]].push_back(u);
        }
        vector<set<ll>> s(n+1);
        vector<ll> ans(n+1);
        for(ll i = path.size()-1; i>=0; i--){
            ll u = path[i];
            s[u].insert(color[u]);
            for(ll x: c[u]){
                if(s[x].size() > s[u].size()){
                    s[u].swap(s[x]);
                }
                for(ll v:s[x]) s[u].insert(v);
            }
            ans[i]=s[u].size();
        }
        fi(1,n+1){
            cout<<ans[i]<<" ";
        }
    }
    return 0;
}
