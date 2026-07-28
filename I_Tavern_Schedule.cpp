// رَبَّنَا آتِنَا مِن لَّدُنكَ رَحْمَةً وَهَيِّئْ لَنَا مِنْ أَمْرِنَا رَشَدًا

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(a) a.begin(), a.end()
#define endl "\n"
#define AMR                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);
ll lcm(ll a, ll b) { return (a * b) / __gcd(a, b); }
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
typedef unsigned __int128 bll;
const ll MOD = 1e9 + 7;
const ld pi = acos(-1);
///////////////////////fast exponentiation ///////////////////

const int MAXN = 2e6;

ll fact[MAXN + 1];
ll invFact[MAXN + 1];

ll power(ll base, ll exp)
{
    ll res = 1;
    base %= MOD;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n)
{
    return power(n, MOD - 2);
}
/*

Vandermonde's Identity

sumtion (i = 1 to k)[  [ k-1 C i-1 ] * [x , j] ]  ==  [ k+x+1 C  k ]

Hockey-stick identity

sumtion (i = x to k ) (i C x) == k+1 C n+1

*/
void precompute()
{
    fact[0] = 1;
    invFact[0] = 1;

    for (int i = 1; i <= MAXN; i++)
    {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[MAXN] = modInverse(fact[MAXN]);
    for (int i = MAXN - 1; i >= 1; i--)
    {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

ll C(int n, int r)
{
    if (r < 0 || r > n || n > MAXN)
        return 0;
    ll num = fact[n];
    ll den = (invFact[r] * invFact[n - r]) % MOD;
    return (num * den) % MOD;
}

ll P(int n, int r)
{
    if (r < 0 || r > n || n > MAXN)
        return 0;
    ll num = fact[n];
    ll den = invFact[n - r];
    return (num * den) % MOD;
}

ll small_r_C(ll n, ll r)
{
    if (r < 0 || r > n)
        return 0;
    ll num = 1;
    ll den = 1;
    for (ll i = 1; i <= r; i++)
    {
        num = (num * ((n - i + 1) % MOD)) % MOD;
        den = (den * i) % MOD;
    }
    return (num * modInverse(den)) % MOD;
}

////////////////////////////////////////////////////////////////////

void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, m, k;
    cin >> n >> m >> k;

    ll res = 0;
    for (ll i = 1; i <= min(k, n - k + 1); i++)
    {
        ll ans = 0;
        ans += C(n - k + 1, i) % MOD;
        ans %= MOD;

        ans *= C(k - 1, i - 1) % MOD;
        ans %= MOD;

        ans *= power(m, i) % MOD;
        ans %= MOD;

        ans *= power(m - 1, k - i) % MOD;
        ans %= MOD;

        res = (res + ans )%MOD ; 
    }
    cout << res << endl ;
}
int main()
{
    AMR

        ll tt = 1;
    cin >> tt;
    precompute();
    while (tt--)
    {
        SOLVE();
    }
}