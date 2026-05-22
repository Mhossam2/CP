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
struct FenwickTree {
    vector<int> bit;
    int n;

    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }

    // Add 'val' to index i (1-based)
    void update(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += i & -i;
        }
    }

    // Query sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i;
        }
        return sum;
    }

    // Query sum from l to r
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    fi(1, t + 1)
    {
        ll n, m, k;
        cin >> n >> m >> k;
        vll a(m + 1, 0);
        FenwickTree sg(m + 1);
        vector<pair<ll, ll>> queries;
        fj(0, k)
        {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;
            queries.push_back({l, r});
        }
        sort(all(queries));
        ll cnt = 0;
        fj(0, k)
        {
            cnt += sg.query(queries[j].second + 1, m+1);
            sg.update(queries[j].second + 1, 1);
        }
        cout << "Test case " << i << ": " << cnt << endl;
    }
    return 0;
}
