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
const ll N=1e6+5;
ll fct[N],invfct[N];
void factorials() {
    fct[0] = 1;
    for(ll i = 1; i < N; i++)
        fct[i] = (fct[i - 1] * i) % MOD;
    invfct[N - 1] = modPow(fct[N - 1], MOD - 2, MOD);
    for(ll i = N - 2; i >= 0; i--)
        invfct[i] = (invfct[i + 1] * (i + 1)) % MOD;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    factorials();
    while (t--)
    {
        ll n;cin>>n;
        ll num = mul(fct[2*n-1], mul(invfct[n-1],invfct[n],MOD), MOD);
        cout << add(add(num,num,MOD), -1*n,MOD);
    }
    return 0;
}