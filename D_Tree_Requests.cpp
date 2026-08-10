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
ll n,m;
vector<ll> In;
vector<ll> Out;
vector<vector<pair<ll,ll>>> H;  //H[1] =  
vector<ll> depth;
vector<vector<ll>> adj;
string s;
ll ti=0;
void dfs(ll node, ll parent)
{
    ti++;
    In[node] = ti;
    H[depth[node]].push_back(make_pair(ti, s[node]-'a'));
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        depth[nxt] = depth[node]+1;
        dfs(nxt, node);
    }
    ti++;
    Out[node] = ti;
}
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        cin >> n >> m;
        adj.assign(n, {});
        fi(1, n){
            ll x;cin>>x;
            x--;
            adj[x].push_back(i);
            adj[i].push_back(x);
        }
        cin>>s;
        In.assign(n, 0);
        Out.assign(n, 0);
        depth.assign(n,0);
        H.assign(n+5,{});
        dfs(0,-1);
        vector<vector<array<int,26>>> pref(H.size());  
        fi(0,pref.size()){
            pref[i].assign(H[i].size()+1,{});
            fj(0,H[i].size()){
                pref[i][j+1] = pref[i][j];
                pref[i][j+1][H[i][j].second]++;
            }
        }
        fi(0,m){
            ll v,h;cin>>v>>h;
            v--;h--;
            ll l = lower_bound(H[h].begin(), H[h].end(), make_pair(In[v], (ll)-1)) - H[h].begin();
            ll r = lower_bound(H[h].begin(), H[h].end(), make_pair(Out[v]+1, (ll)-1)) - H[h].begin();
            ll ok = 0;
            fj(0,26){
                if((pref[h][r][j]-pref[h][l][j])%2!=0) ok++;
            }
            if(ok<2) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
    return 0;
}
