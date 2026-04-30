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
long long mul(long long x, long long y, const long long &mod) { return ((x % mod) * (y % mod)) % mod; }
long long add(long long x, long long y, const long long &mod) { return (((x % mod) + (y % mod)) % mod + mod) % mod; }
long long modPow(long long a, long long b, ll mod) {
    long long res = 1;
    while(b > 0) {
        if(b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

const ll MOD = 1e9+7;
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<pair<ll,ll>> a;
        ll mx=0;
        fi(0,n){
            ll x,y;cin>>x>>y;
            a.push_back({x,y});
        }
        ll cnt = 1;
        ll cnt2 = 1;
        fi(0,n){
            cnt = mul(a[i].second + 1, cnt, MOD);
            cnt2 = mul(a[i].second + 1, cnt2, MOD-1);
        }
        ll sum = 1;
        fi(0,n){
            ll upper = add(1, mul(-1, modPow(a[i].first, a[i].second+1, MOD), MOD), MOD);
            ll lower = modPow(1 - a[i].first, MOD-2, MOD);
            sum = mul(mul(upper, lower, MOD), sum, MOD);
        }
        ll num = 1;
        fi(0,n){
            num = mul(num, modPow(a[i].first, a[i].second, MOD), MOD);
        }
        ll upper = (cnt2%mul(2, MOD - 1, MOD))/2;
        ll product = modPow(num, upper, MOD);
        cout << cnt <<" "<< sum <<" "<< product;
    }
    return 0;
}