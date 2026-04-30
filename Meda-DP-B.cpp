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
const ll MOD=1e9+7;
ll x,n;
ll X = 1e6+1;
ll N=100;
vector<ll> a(N);
vector<ll> dp(X, -1);
ll dfs(ll sum){
    if(sum == x) return 1;
    if(sum > x) return 0;
    if(dp[sum] != -1) return dp[sum];
    ll ans = 0;
    fi(0,n){
        ans += dfs(sum + a[i])%MOD;
        ans %= MOD;
    }
    return dp[sum]=ans;
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> x;
        fi(0, n){
            cin>>a[i];
        }
        vector<ll> dp(x+1, 0);
        dp[x] = 1;
        for(ll i = x; i >= 0; i--){
            fj(0,n){
                if(i - a[j] < 0) continue;
                dp[i - a[j]] += dp[i]%MOD;
                dp[i - a[j]] %= MOD;
            }
        }
        cout << dp[0];
        //cout<<dfs(0)<<endl;
    }
    return 0;
}
