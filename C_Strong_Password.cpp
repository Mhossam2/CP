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
bool working[100001];
bool dead[100001];
bool dp[100001]; // dp[new_rem] = min(dp[new_rem], dp[oldrem]+1)
bool dfs(ll val, string &ans)
{
    if (dead[val])
        return 0;
    if (val == 0)
        return 1;
    working[val] = 1;
    ll v0 = (val * 10) % n;
    if (!working[v0] && !dead[v0]) {
        ans.push_back('0');
        if (dfs(v0, ans)) {
            working[val] = false; 
            return true;
        }
        ans.pop_back();
    }

    ll v1 = (val * 10 + d) % n;
    if (!working[v1] && !dead[v1]) {
        ans.push_back(char('0' + d));
        if (dfs(v1, ans)) { working[val] = false; return true; }
        ans.pop_back();
    }

    working[val] = false;
    dead[val] = true;
    return false;
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
        fi(0, 100001){
            working[i] = 0;
            dead[i]=0;
        }
        string ans = to_string(d);
        dfs(d % n, ans);
        cout << ans << endl;
    }
    return 0;
}
