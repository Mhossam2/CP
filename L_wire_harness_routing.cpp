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
void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> p(n);

    for (ll i = 0; i < n; i++)
    {
        cin >> p[i].first >> p[i].second;
    }

    vector<pair<ll, ll>> wires;

    for (ll i = 0; i < m; i++)
    {
        ll x;
        cin >> x;
        wires.push_back({x, i + 1});
    }

    for (ll s = 0; s <= 1; s++)
    {
        vector<pair<ll, ll>> ans;
        for (ll i = s; i < n; i += 2)
        {
            ll prev = (i - 1 + n) % n;
            ll next = (i + 1) % n;
            ll d = (abs(p[prev].first - p[i].first) + abs(p[i].second - p[prev].second)) + 
                   (abs(p[i].first - p[next].first) + abs(p[i].second - p[next].second));

            ans.push_back({d, i});
        }

        map<ll, vector<ll>> vis; 

        for (auto &i : wires)
        {
            vis[i.first].push_back(i.second);
        }

        bool can = 1;
        vector<ll> a(n, -1);

        for (auto req : ans)
        {
            if (vis[req.first].empty())
            {
                can = 0;
                break; 
            }
            
            a[req.second] = vis[req.first].back(); 
            vis[req.first].pop_back();
        }

        if (can)
        {
            cout << "YES" << endl;

            for (ll &i : a)
                cout << i << ' ';
            cout << endl;

            return;
        }
    }

    cout << "NO\n";
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
