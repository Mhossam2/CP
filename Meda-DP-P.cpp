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
ll n, k;
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> k;
        vector<int> cnt2(n), cnt5(n);
        fi(0, n)
        {
            ll x;cin >> x;
            ll cnt = 0;
            while (x % 2 == 0)
            {
                x /= 2;
                cnt++;
            }
            cnt2[i] = cnt;
            cnt = 0;
            while (x % 5 == 0)
            {
                x /= 5;
                cnt++;
            }
            cnt5[i] = cnt;
        }
        const int MAX5 = 26*n;
        vector<vector<int>> dp(k + 2, vector<int>(MAX5, -1e9));
        vector<vector<int>> dp1(k + 2, vector<int>(MAX5, -1e9));
        int ans = 0;
        dp[0][0] = 0;
        for (ll i = 0; i < n; i++)
        {
            for (ll taken = 0; taken <= k; taken++)
            {
                for (ll cnt = 0; cnt < MAX5; cnt++)
                {
                    if (dp[taken][cnt] < 0)
                        continue;
                    dp1[taken][cnt] = max(dp[taken][cnt], dp1[taken][cnt]);                                       // leave a[i];
                    dp1[taken + 1][cnt + cnt5[i]] = max(cnt2[i] + dp[taken][cnt], dp1[taken + 1][cnt + cnt5[i]]); // take a[i];
                }
            }
            swap(dp1, dp);
        }
        for (int i = 0; i < MAX5; i++)
        {
            ans = max(ans, min(i, dp[k][i]));
        }
        cout << ans << endl;
    }
    return 0;
}