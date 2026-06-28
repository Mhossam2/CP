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
ll modPow(ll a, ll b, ll mod)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod; // O( log b )
        b >>= 1;
    }
    return res;
}
ll modInverse(ll n, ll mod)
{
    return modPow(n, mod - 2, mod);
}

ll n, d;
ll dp[100001]; // dp[new_rem] = min(dp[new_rem], dp[oldrem]+1)
ll dfs(ll val)
{
    if (dp[val] != -1)
        return dp[val];
    if (val == 0)
        return 0;
    ll res = 1e18;
    res = min(res, 1 + dfs((val * 10) % n));
    res = min(res, 1 + dfs((val * 10 + d) % n));
    return dp[val] = res;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        cin >> n >> d;
        fi(0, 100001) dp[i] = -1;
        dfs(d % n);
        string ans = "";
        ll len = dp[0];
        ll val = 0;
        while (len != -1)
        {
            ll num1 = ((val - d) / 10) % n;
            ll res1 = dp[num1];

            ll num2 = ((val) / 10) % n;
            ll res2 = dp[num2];

            if (res1 == -1)
            {
                val = num2;
                ans += "0";
            }
            else
            {
                val = num1;
                ans += to_string(d);
            }
            len--;
        }
    }
    return 0;
}
