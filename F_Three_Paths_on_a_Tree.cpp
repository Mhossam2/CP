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
vector<ll> finddiameter(vector<vector<ll>> &adj, ll n){
    auto bfs = [&](ll start){ //return the farest node from the start node and parent of each node
        vector<ll> parent(n, -1), dist(n, 0);
        queue<ll> q;
        q.push(start);
        ll far = start;
        while(!q.empty()){
            ll node = q.front(); q.pop();
            far = node;
            for(ll child : adj[node]){
                if(child != parent[node]){
                    parent[child]=node;
                    dist[child]=dist[node]+1;
                    q.push(child);
                }
            }
        }
        return make_pair(far, parent);
    };
    auto [start,_] = bfs(0);  //get the farest node from any random node (ans = 1st diameter node)
    auto [end,par] = bfs(start); //get the 2nd diameter node(farest node from the first diameter node)
    vector<ll> path;
    ll i = end;
    while(i != -1){ //get the whole path
        path.push_back(i);
        i = par[i];
    } 
    return path;
}
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
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
        auto x = finddiameter(adj, n);
        if(x.size() == n){
            cout<<n-1<<endl;
            cout<<x[0]+1<<" "<<x[1]+1<<x[n-1]+1;
        }
        else{
            queue<ll> q;
            vector<ll> dist(n, 0);
            fi(0,x.size()){
                q.push(x[i]);
            }
            ll far = x[1];
            while(!q.empty()){
                ll node = q.front(); q.pop();
                for(ll child:adj[node]){
                    if(dist[child] >= dist[node]+1){
                        dist[child] = dist[node]+1;
                        q.push(child);
                    }
                }
            }
            fi(0,n){
                if(dist[i] > dist[far]){
                    far=i;
                }   
            }
            cout<<x.size() - 1 + dist[far]<<endl;
            cout<<x[0]+1<<" "<<x[x.size()-1]+1<<" "<<far+1<<endl;
        }
    }
    return 0;
}
