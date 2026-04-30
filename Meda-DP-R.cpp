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
ll n;
ll dp[101][10001];
vector<ll> a,b;
ll sum;
ll dfs(ll i, ll sumA)
{
    if (i == n)
        return sumA*sumA + (sum-sumA)*(sum-sumA);
    if (dp[i][sumA] != -1)
        return dp[i][sumA];
    ll ans = 1e18;
    ans = min(ans, dfs(i + 1, sumA+a[i]));
    ans = min(ans, dfs(i+1, sumA + b[i]));
    return dp[i][sumA] = ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        cin >> n;
        a.clear();
        b.clear();
        fi(0,101){
            fj(0,10001){
                dp[i][j]=-1;
            }
        }
        sum=0;
        ll ss=0;
        fi(0,n){
            ll x;cin>>x;
            a.push_back(x);
            sum += a[i];
            ss += a[i]*a[i];
        }
        fi(0,n){
            ll x;cin>>x;
            b.push_back(x);
            sum+=b[i];
            ss += b[i]*b[i];
        }
        ll ans = dfs(0,0);
        cout<< dfs(0,0) + (n-2) *ss<<endl;


    }
    return 0;
}