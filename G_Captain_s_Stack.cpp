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
const ll MOD = 998244353;
const ld pi = acos(-1);

void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll q;
    cin >> q;

    ll sm = 0;

    vector<ll> s;
    while (q--)
    {
        string ss;
        cin >> ss;

        if (ss == "Push")
        {
            ll x;
            cin >> x;
            s.push_back(x);
            sm += x % MOD;
            sm %= MOD;
        }

        if (ss == "Repeat")
        {
            sm *= 2;
            sm %= MOD;

            if (s.size() <= q + 1)
            {
                vector<ll> nw = s;
                for (ll &i : s)
                    nw.push_back(i);

                s = nw;
            }
        }

        if (ss == "Pop")
        {
            ll x = s.back();
            s.pop_back();

            sm -= x;
            sm += MOD;
            sm %= MOD;
        }
        cout << sm << endl;
    }
}
int main()
{
    AMR

        ll tt = 1;
    // cin >> tt;
    while (tt--)
    {
        SOLVE();
    }
}