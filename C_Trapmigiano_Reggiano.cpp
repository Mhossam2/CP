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
    cin >> t;
    while (t--)
    {
        ll n,st,en;cin>>n>>st>>en;
        st--;
        en--;
        vector<vector<ll>> adj(n);
        fi(0,n-1){
            ll x,y;cin>>x>>y;
            x--;y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }   
        queue<ll> q;
        vector<ll> path;
        path.push_back(en);
        q.push(en);
        vll dist(n,1e18);
        dist[en]=0;
        while(!q.empty()){
            ll node= q.front(); q.pop();
            for(ll nxt: adj[node]){
                if(dist[nxt]>dist[node]+1){
                    q.push(nxt);
                    path.push_back(nxt);
                    dist[nxt]=dist[node]+1;
                }
            }
        }
        reverse(all(path));
        fi(0,n) cout<<path[i]+1<<" ";
        cout<<endl;
    }
    return 0;
}
