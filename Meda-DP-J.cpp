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
const ll MOD = 1e9 +7; 
ll n,m;
ll dp[1001][1001];
ll dfs(ll i,ll j, vector<vector<ll>> &adj){
    if(i==n-1 && j==m-1) return 1;
    if(dp[i][j] != -1) return dp[i][j];
    ll ans=0;
    if(in(i+1,j,n,m)){
        if(adj[i+1][j]){
            ans+= dfs(i+1,j,adj)%MOD;
            ans%=MOD;
        }
    }
    if(in(i,j+1,n,m)){
        if(adj[i][j+1]){
            ans+= dfs(i,j+1,adj)%MOD;
            ans%=MOD;
        }
    }
    return dp[i][j]=ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin>>n>>m;
        vector<vector<ll>> adj(n,vector<ll> (m));
        fi(0,n){
            fj(0,m){
                char c;cin>>c;
                adj[i][j]=(c=='.');
            }
        }
        fi(0,n){
            fj(0,m){
                dp[i][j] = -1;
            }
        }
        cout<<dfs(0,0,adj);
        
        
        
    }
    return 0;
}