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

void solve()
{
    ll n, q;

    cin >> n >> q;

    vector<ll> a(n + 1);

    for (ll i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    vector<vector<ll>> adj(n + 1);

    for (ll i = 1; i < n; i++)
    {
        ll x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<ll> ans(n + 1);

    ll sm = 0, sz = 0;
    map<ll, ll> fq;

    auto dfs = [&](auto &self, ll v, ll u) -> void
    {
        sm += a[v];
        fq[a[v]]++;
        sz++;

        bool T = 0;
        ll del = -1e18;

        if (sm < 0)
        {
            auto it = fq.begin();
            del = it->first;
            sm -= del;

            it->second--;
            sz--;
            if (it->second == 0)
            {
                fq.erase(it);
            }
            T = 1;
        }

        ans[v] = sz;

        for (ll ch : adj[v])
        {
            if (ch == u)
                continue;
            self(self, ch, v);
        }

        if (T)
        {
            fq[del]++;
            sz++;
            sm += del;
        }

        sz--;
        sm -= a[v];
        fq[a[v]]--;

        if (fq[a[v]] == 0)
        {
            fq.erase(a[v]);
        }
    };
    dfs(dfs, 1, 0);

    while (q--)
    {
        ll k;
        cin >> k;

        ll pf_xor = 0;

        for (ll i = 0; i < k; i++)
        {
            ll x;
            cin >> x;
            pf_xor ^= ans[x];
        }
        cout << (pf_xor == 0 ? "Osama" : "Amadoo") << endl;
    }
}

int main()
{
    // بسم الله
    AMR

        ll tt = 1;
    cin >> tt;
next:
    while (tt--)
    {
        solve();
    }
}