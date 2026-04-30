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
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll w, h, d, n;
        cin >> w >> h >> d >> n;
        ll mul = w * h * d;
        if ((((w % n) * (h % n)) % n * (d % n)) % n != 0)
            cout << -1 << endl;
        else
        {
            ll x = __gcd(n, w);
            ll y = __gcd(n / x, h);
            ll z = __gcd(n / (x * y), d);
            if (n == x * y * z)
                cout << x - 1 << " " << y - 1 << " " << z - 1 << endl;
            else
                cout << -1 << endl;
        }
    }
    return 0;
}
