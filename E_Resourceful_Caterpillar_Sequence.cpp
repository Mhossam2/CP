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
        ll n;cin>>n;
        vector<vector<ll>> adj(n);
        fi(0,n-1){
            ll u,v;cin>>u>>v;
            u--;v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<ll> deg(n);
        ll leafs=0;
        fi(0,n) leafs += adj[i].size()==1;
        ll ans = leafs*(n-leafs);
        ll cnt = 0;
        vector<ll> adjleaf(n);
        fi(0,n){
            if(deg[i] > 1){
                for(ll v:adj[i]){
                    adjleaf[i] += adj[v].size()==1;
                }
            }
            cnt += adjleaf[i] == 0;
        }
        fi(0,n){
            if(deg[i] > 1 && adjleaf[i] > 0 && adjleaf[i] < deg[i]){
                ans += cnt * (deg[i] - adjleaf[i] - 1);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
