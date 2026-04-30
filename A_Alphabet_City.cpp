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
bool f(ll mid, vector<ll> &total, vector<vector<ll>> &Occ, ll ind)
{
    for (ll i = 0; i < 26; i++)
    {
        if (!(m * (total[i] - Occ[ind][i]) >= mid * (total[i] - Occ[ind][i]) + Occ[ind][i]))
            return false;
    }
    return true;
}
ll binary_search1(vector<ll> &total, vector<vector<ll>> &pos, ll ind)
{
    ll l = 0, r = m;
    ll ans = -1;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (f(mid, total, pos, ind))
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n >> m;
        vector<ll> total(26, 0);
        vector<vector<ll>> pos(n, vector<ll>(26, 0));
        fi(0, n)
        {
            string s;
            cin >> s;
            fj(0, s.size())
            {
                pos[i][s[j] - 'A']++;
                total[s[j] - 'A']++;
            }
        }
        fi(0, n)
        {
            cout << binary_search1(total, pos, i) << " ";
        }
    }
    return 0;
}
