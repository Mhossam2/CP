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
ll n;
ll N=1e6 + 1;
vector<ll> a(N);
vector<ll> dp(N, -1);
ll dfs(ll sum){
    if(sum == n) return 1;
    if(sum > n) return 0;
    if(dp[sum] != -1) return dp[sum];
    ll ans = 0;
    fi(1,7){
        ans += dfs(sum + i)%MOD;
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
        cin >> n;
        cout<<dfs(0)<<endl;
    }
    return 0;
}
