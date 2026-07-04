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
const ll MOD = 1e9 + 7;
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        if (n > 18)
        {
            cout << "S";
            continue;
        }
        ll s = 0;
        vll a(n);
        fi(0, n)
        {
            cin >> a[i];
            s += a[i];
        }
        set<ll> ss;
        bool x = 0;
        for (ll i = 0; i < (1LL << n); i++)
        {
            ll sm = 0;
            fj(0, n)
            {
                if (i & (1 << j))
                {
                    sm += a[j];
                }
            }
            if (ss.count(sm))
            {
                x = 1;
                break;
            }
            else
            {
                ss.insert(sm);
            }
        }
        if (x)
        {
            cout << "S";
        }
        else
            cout << "N";
    }
    return 0;
}
