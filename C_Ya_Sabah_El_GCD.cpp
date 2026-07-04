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
const ll MOD = 1e9 + 7;

vector<ll> get_factors(ll n) {
    vector<ll> primes;
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            primes.push_back(d);
            while (n % d == 0) n /= d;
        }
    }
    if (n > 1) primes.push_back(n);
    return primes;
}
const ll N=5000;
ll n;
ll a[5001];
ll b[5001];
ll dp[5001][N];
ll newmask[5001];
ll dfs(ll i,ll mask, vector<ll> &f){
    if(i==n){
        if(mask < (1<<f.size())-1) return 1e12;
        return 0;
    }
    if(dp[i][mask]!=-1) return dp[i][mask];
    ll res = 1e12;
    res = min(res, dfs(i+1,mask,f));
    res = min(res, (i+1)*(i+1) + (i+1) + dfs(i+1,mask|newmask[i],f));
    return dp[i][mask]=res;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin>>n;
        ll g = 0;
        fi(0,n){
            cin>>a[i];
            g=gcd(a[i],g);
        }
        fi(0,n) cin>>b[i];
        fi(0,n){
            fj(0,N) dp[i][j]=-1;
        }
        vector<ll> f = get_factors(g);
        fi(0,n){
            newmask[i] = 0;
            fj(0,f.size()){
                if(b[i]%f[j] != 0){
                    newmask[i] |= (1<<j);
                }
            }
        }
        ll num = dfs(0,0,f);
        if(num >= 1e12) cout<<-1;
        else cout<<num;
 
    }
    return 0;
}
