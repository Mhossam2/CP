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
using namespace std;
ll n;
ll dp[1000005][2];
string x;
string y;
ll dfs(ll i, ll p){
    if(i == n) return 0;
    if(dp[i][p] != -1) return dp[i][p];
    ll ans = 1e9;
    ll cost0 = 0;  // cost to make parity = 0; (y[i]=0)
    if(y[i] != '0') cost0++;  // adjust y to be equal 0
    if((x[i] - '0')^p != 0) cost0++;  //adjust x to make y[0] valid
    ans = min(ans, cost0 + dfs(i+1,0));
    ll cost1 = 0;  // cost to make parity = 1; (y[i]=1)
    if(y[i] != '1') cost1++;
    if((x[i]-'0')^p != 1) cost1++;
    ans = min(ans, cost1 + dfs(i+1,1));
    return dp[i][p] = ans;
}
int main()
{
    HONDA
    int t = 1;
     cin >> t;
    while (t--)
    {
        cin >> x >> y;
        n = x.size();
        fi(0,n+1){
            fj(0,2){
                dp[i][j] = -1;
            }
        }
        cout << dfs(0,0) << endl;
    }
    return 0;
}