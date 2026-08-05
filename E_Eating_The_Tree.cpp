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
        vll a(n);
        fi(0, n) cin >> a[i];
        vector<vector<ll>> adj(n);
        fi(0, n - 1)
        {
            ll u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<ll> deg(n);
        fi(0, n) deg[i] = adj[i].size();
        vector<bool> removed(n + 1, 0);
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        for (ll i = 0; i < n; i++)
            pq.push({a[i], i});
        ll cnt = n;
        vector<pair<ll, ll>> res;
        bool ok = 1;
        while (cnt > 1)
        {
            ll node = -1;
            while (!pq.empty())
            {
                auto x = pq.top();
                pq.pop();
                if (removed[x.second])
                    continue;
                if (x.first != a[x.second])
                    continue;
                node = x.second;
                break;
            }
            if (deg[node] > 1)
            {
                ok = false;
                break;
            }
            ll nb = -1;
            for (ll x : adj[node])
            {
                if (!removed[x])
                {
                    nb = x;
                    break;
                }
            }
            if (nb == -1)
            {
                ok = false;
                break;
            }
            if (a[nb] > a[node])
            {
                a[nb] += a[node];
                res.push_back({nb, node});
                removed[node] = 1;
                deg[nb]--;
                cnt--;
                pq.push({a[nb], nb});
            }
            else
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cout << "Yes" << endl;
            for (auto p : res)
                cout << p.first + 1 << " " << p.second + 1 << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}
