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
void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, m;
    cin >> n >> m;

    vector<ll> a(n), s;
    vector<pair<ll, ll>> v;
    map<ll, ll> fq;

    ll cnt_ev = 0, cnt_od = 0;

    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
        fq[a[i]]++;
        if (fq[a[i]] == 1)
        {
            v.push_back({a[i], i});
            if (a[i] % 2 == 0)
            {
                cnt_ev++;
            }
            else
            {
                cnt_od++;
            }
        }
        else
        {
            s.push_back(i);
        }
    }


    vector<ll> od, even;

    for (ll i = 1; i <= m; i++)
    {
        if (fq[i])
            continue;

        if (i % 2 == 0)
        {
            even.push_back(i);
        }
        else
        {
            od.push_back(i);
        }

        if (even.size() > n && od.size() > n)
            break;
    }

    ll ans = 0;

    for (ll i = 0; i < s.size(); i++)
    {
        if (cnt_ev <= cnt_od)
        {
            if (even.empty())
            {
                cout << -1 << endl;
                return;
            }
            a[s[i]] = even.back();
            even.pop_back();
            cnt_ev++;
        }
        else
        {
            if (od.empty())
            {
                cout << -1 << endl;
                return;
            }
            a[s[i]] = od.back();
            od.pop_back();
            cnt_od++;
        }
        ans ++ ; 
    }

    //  cout << cnt_ev << ' ' << cnt_od << endl ;
    // for(ll i : a)cout << i << ' ' ;

    ll ptr = 0 ;
    while (cnt_ev != cnt_od)
    {

        if (cnt_ev > cnt_od)
        {
            while(ptr < n && a[ptr] % 2  == 1 )ptr ++ ; 

             if (od.empty())
            {
                cout << -1 << endl;
                return;
            }

            a[ptr] = od.back();
            od.pop_back();
            cnt_od++;
            cnt_ev -- ; 

        }
        else
        {
               while(ptr < n && a[ptr] % 2  == 0 )ptr ++ ; 

            if (even.empty())
            {
                cout << -1 << endl;
                return;
            }
            a[ptr] = even.back();
            even.pop_back();
            cnt_ev++;
            cnt_od -- ; 
        }
        ans ++ ; 
    }

    cout << ans << endl ;  

    for(ll i : a)cout << i << ' ' ;
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