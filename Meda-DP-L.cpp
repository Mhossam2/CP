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
ld dp[301][301][301];
ld dfs(ll c1,ll c2, ll c3){
    if(c1 + c2 + c3 == 0) return 0;
    if(dp[c1][c2][c3] != -1) return dp[c1][c2][c3];
    ld ans = 1;
    if(c1) ans += (1.0 * c1)/n * dfs(c1-1,c2,c3);
    if(c2) ans += 1.0 * c2/n * dfs(c1+1,c2-1,c3);
    if(c3) ans += 1.0 * c3/n * dfs(c1, c2+1 ,c3-1);
    ans /= 1 - (n * 1.0 - c1 - c2 - c3) / n;
    return dp[c1][c2][c3] = ans;
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
        ll cnt1,cnt2,cnt3;
        cnt1 = cnt2 = cnt3 = 0;
        fi(0,n){
            ll x;cin>>x;
            cnt1 += x==1;
            cnt2 += x==2;
            cnt3 += x==3;
        }
        fi(0,301){
            fj(0,301){
                for(ll k=0;k<301;k++){
                    dp[i][j][k] = -1;
                }
            }
        }
        cout << fixed << setprecision(10) << dfs(cnt1,cnt2,cnt3);        
    }
    return 0;
}