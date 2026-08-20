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
// const ll MOD = 1e9 + 7;
const ld pi = acos(-1);
void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, k;
    cin >> n >> k;

    vector<ll> ans(k, 1e18);
    ll mx=0;
    vector<string> a(n);
    for (auto &i : a)
        cin >> i;
    vector<vector<ll>> remp(n);
    for (ll i = 0; i < n; i++)
    {
        ll num = 0;
        ll len=a[i].size();
        mx=max(mx, len);
        remp[i].push_back((a[i][0] - '0') % k);
        //cout<<remp[i][0]<<" ";
        for (ll j = 1; j < a[i].size(); j++)
        {
            ll num = ((remp[i][j - 1] * (10%k)) % k + ((a[i][j] - '0') % k)) % k;
            remp[i].push_back(num);
            //cout<<remp[i][j]<<" ";
        }
        //cout<<endl;
    }
    vector<ll> pow10(mx + 1);
    pow10[0] = 1 % k;
    for (ll i = 1; i <= mx; i++)
        pow10[i] = (pow10[i - 1] * 10) % k;

    vector<ll> dist(k, 1e18);
    //vector<ll> vis(k,0);

    priority_queue<pair<ll, ll> , vector<pair<ll,ll>> , greater<> > p;
    dist[0] = 0;
    p.push({0, 0});
    while (!p.empty())
    {
        auto [len, rem] = p.top();

        p.pop();
        if(dist[rem] < len)continue;
        for (ll i = 0; i < n; i++)
        {
            for (ll j = 0; j < a[i].size(); j++)
            {
                ll r = remp[i][j];
                ll newrem = (rem * pow10[j + 1] % k + r) % k;
                if (dist[newrem] > len + j+1)
                {
                    dist[newrem] = len + j+1;
                    p.push({dist[newrem], newrem});

                   //cout << len << ' ' << rem << ' ' << newrem << ' ' << len + j  <<endl;; 
                }
            }
        }

    }
    for (ll i : dist)
    if(i>1e9) cout<<-1<<" ";
    else
        cout << i << " ";

    cout<<endl;
}

int main()
{
    AMR

        ll tt = 1;
    cin >> tt;
    while (tt--)
    {
        SOLVE();
    }
}