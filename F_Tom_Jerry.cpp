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

void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> adj(n + 1), par(n + 1);

    vector<ll> a(n);
    for (ll &i : a)
        cin >> i;

    
    for (ll i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        par[y].push_back(x);
    }
    vector<ll> topo;
    vector<ll> vis(n + 1, 0);
    auto dfs = [&](auto &&self, ll u) -> void
    {
        vis[u] = 1;

        for (ll ch : adj[u])
        {
            if (vis[ch])
                continue;

            self(self, ch);
        }
      
        topo.push_back(u);
    
    };
    
    for(ll i = 1 ; i <= n ; i ++)
    {
        if(par[i].empty() && !adj[i].empty())
        {
            dfs(dfs ,i) ;
        }
    } 
    reverse(all(topo)) ; 

    for(ll i : topo)cout << i<< ' ' ; 
    cout << endl;
    auto fn = [&](ll x) -> bool 
    {
        ll mx=0;
        vector<ll> dp(n + 1, 0);

        for (ll &i : topo)
        {
            
            for (ll &j : adj[i])
            {
                dp[i] = max(dp[j], dp[i]);
                mx = max(mx,dp[i]);

            }
            dp[i] += (a[i - 1] < x);
            mx=max(dp[i],mx);
            //   cout << i << ' ' << dp[i] << ' ' << a[i-1] << endl ;
        }
        return (mx >= x);
    };

    ll ans = 1;
    ll l = 2, r = n + 1;

    while (l <= r)
    {
        ll md = (l + r) / 2;

        if (fn(md))
        {
            l = md + 1;
            ans = md;
        }
        else
        {
            r = md - 1;
        }
    }
    cout << ans << endl;
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