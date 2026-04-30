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
ld dp[3001][3001];
ld dfs(ll i,ll heads, vector<ld> &p){
    if(i == n){
        if(n/2 >= heads){
            return 0;
        }
        else{
            return 1;
        }
    }
    if(dp[i][heads] != -1) return dp[i][heads];
    ld ans = 0;
    ans += p[i] * dfs(i+1, heads + 1, p);
    ans += (1.0 - p[i]) * dfs(i+1, heads, p);
    return dp[i][heads] = ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> n;
        vector<ld> p(n);
        fi(0,n) cin>>p[i];
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                dp[i][j] = -1.0;
            }
        }
        cout << fixed << setprecision(10) << dfs(0,0,p);
        
        
    }
    return 0;
}