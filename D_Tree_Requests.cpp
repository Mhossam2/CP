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
vector<vector<pair<ll,ll>>> H(1e6+5);
vector<ll> depth;
vector<vector<ll>> adj;
string s;
ll ti=0;
void dfs(ll node, ll parent)
{
    ti++;
    In[node] = ti;
    for (ll nxt : adj[node])
    {
        if (nxt == parent)
            continue;
        depth[nxt] = depth[node]+1;
        H[depth[node]].push_back(make_pair(ti, s[node]-'0'));
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
        fi(0, n){
            ll x;cin>>x;
            adj[x].push_back(i);
            adj[i].push_back(x);
        }
        In.assign(n, 0);
        Out.assign(n, 0);
        depth.assign(n,0);
        dfs(0,-1);
        vector<vector<map<ll,ll>>> pref(1e6+5);
        fi(0,1e6+5){
            pref[i].assign(H[i].size(),{});
            fj(0,pref[i].size()){
                pref[i][j][H[i][j].second]++;
            }
        }
        fi(0,m){
            ll v,h;cin>>v>>h;
            v--;h--;
            ll l = lower_bound(H[h].begin(), H[h].end(), make_pair(In[v], -1)) - H[h].begin() - 1;
		    ll r = lower_bound(H[h].begin(), H[h].end(), make_pair(Out[v], -1)) - H[h].begin() - 1;
            bool ok = 1;
            fj(0,26){
                if((pref[h][r][i]-pref[h][l][i])%2!=0) ok = 0;
            }
            if(ok) cout<<"Yes"<<endl;
            else cout<<"No"<<endl;
        }
    }
    return 0;
}
