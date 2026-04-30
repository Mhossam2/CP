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
ll n, m;
vector<string> a;
string target = "narek";
ll dp[1005][5];
ll solve(ll i, ll j) {
    if (i == n) return 0;
    ll &ans = dp[i][j];
    if (ans != -1) return ans;
    ans = solve(i + 1, j); //leave string

    ll cur = j, cnt = 0, used = 0, tot = 0;
    for (char c : a[i]) {
        if (c == 'n' || c == 'a' || c == 'r' || c == 'e' || c == 'k') {
            tot++;
            if (c == target[cur]) {
                cur++;
                if (cur == 5) {
                    used += 5;
                    cnt++;
                    cur = 0;
                }
            }
        }
    }
    ans = max(ans, cnt * 5 - (tot - used) + solve(i + 1, cur));
    return ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
     cin >> t;
    while (t--)
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &s : a) cin >> s;
        memset(dp, -1, sizeof(dp));
        cout<<solve(0, 0)<<endl;   
    }
    return 0;
}