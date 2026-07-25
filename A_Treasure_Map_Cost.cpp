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
vector<vector<ll>> adj;
vector<ll> subtreeSize;

ll dfs(ll node, ll parent) {
    ll size = 1;
    for (ll child : adj[node]) {
        if (child != parent) {
            size += dfs(child, node);
        }
    }
    subtreeSize[node] = size;
    return size;
}
const int MOD = 1e9 + 7;
const int MAXN = 200005;

long long fact[MAXN], invFact[MAXN];

long long power(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2, MOD); // Fermat's inverse
    for (int i = MAXN - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    precompute();
    while (t--)
    {
        ll n,k;cin>>n>>k;
        adj.assign(n+1,{});
        subtreeSize.assign(n+1,0);
        vector<pair<ll,ll>> edges(n-1);
        fi(0,n-1){
            ll x,y;cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
            edges[i].first=x;
            edges[i].second=y;
        }
        dfs(1,0);
        ll ans=0;
        fi(0,n-1){
            if(subtreeSize[edges[i].first]<subtreeSize[edges[i].second]) swap(edges[i].first,edges[i].second);
            ans = ((ans + nCr(n,k) - nCr(subtreeSize[edges[i].second],k) - nCr(n - subtreeSize[edges[i].second],k)) % MOD + MOD) % MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}
