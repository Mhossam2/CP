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
ll n;
ll N = 1e5 +1;
vector<vector<ll>> dp(N, vector<ll>(3,-1));
ll dfs(ll i, ll last ,vector<ll> &a, vector<ll> &b, vector<ll> &c){
    if(dp[i][last] != -1) return dp[i][last];
    if(i == n) return 0;
    ll ans = 0;
    for(ll j =0; j<3; j++){
        if(j==last && i!=0) continue;
        if(j == 0) ans = max(ans, a[i] + dfs(i+1, j, a, b, c));
        else if(j == 1) ans = max(ans, b[i] + dfs(i+1, j, a, b, c));
        else ans = max(ans, c[i] + dfs(i+1, j, a, b, c));
    }
    return dp[i][last] = ans;
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin>>n;
        vector<ll> a(n),b(n),c(n);
        fi(0,n){
            cin>>a[i]>>b[i]>>c[i];
        }
        vector<vector<ll>> dp(n+1, vector<ll>(3,0));
        for(ll i = n-1; i >= 0; i--){
            for(ll j = 0; j < 3; j++){
                for(ll k = 0; k < 3; k++){
                    if(k == j) continue;
                    if(k == 0) dp[i][j] = max(dp[i+1][k] + a[i], dp[i][j]);
                    else if(k == 1)  dp[i][j] = max(dp[i+1][k] + b[i], dp[i][j]);
                    else dp[i][j] = max(dp[i+1][k] + c[i], dp[i][j]);
                }
            }
        }
        cout << max({dp[0][0],dp[0][1],dp[0][2]});
    }
    return 0;
}
