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
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> even, odd;
        fi(0, n)
        {
            ll x;
            cin >> x;
            if (x % 2 == 0)
                even.push_back(x);
            else
                odd.push_back(x);
        }
        sort(all(even), greater<ll>());
        sort(all(odd), greater<ll>());
        vector<ll> peven(even.size() + 1, 0);
        fi(1, peven.size())
        {
            peven[i] = peven[i - 1] + even[i - 1];
        }
        fi(0, n)
        {
            if (odd.size() > 0)
            {
                if (even.size() >= i)
                {
                    ll sum = odd[0];
                    sum += peven[i];
                    cout << sum << " ";
                }
                else if ((i - even.size()) % 2 == 0 && odd.size() - 1 >= (i - even.size()))
                {
                    ll sum = odd[0];
                    sum += peven.back();
                    cout << sum << " ";
                }
                else if ((i - even.size()) % 2 == 1 && odd.size() - 1 >= (i - even.size() + 1) && even.size() > 0)
                {
                    ll sum = odd[0];
                    if (peven.size() >= 2)
                        sum += peven[peven.size() - 2];
                    else
                        sum -= odd[0];
                    cout << sum << " ";
                }
                else
                    cout << 0 << " ";
            }
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    return 0;
}
