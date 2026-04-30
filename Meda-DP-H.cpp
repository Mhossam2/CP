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
string s1,s2;
ll dp[3001][3001];
ll dfs(ll i,ll j){
    if(i == s1.size()) return 0;
    if(j == s2.size()) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    ll ans=0;
    if(s1[i] == s2[j]){
        ans += 1 + dfs(i+1,j+1);
    }
    ans = max(dfs(i,j+1),ans);
    ans = max(dfs(i+1,j),ans);
    return dp[i][j] = ans;
}
string out ="";
void build(ll i, ll j){
    if(i == s1.size()) return;
    if(j == s2.size()) return;
    if(s1[i] == s2[j]){
        out += s1[i];
        build(i+1,j+1);
        return;
    }
    if(dp[i+1][j] > dp[i][j+1]){
        build(i+1,j);
    }
    else{
        build(i,j+1);
    }
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        cin >> s1 >> s2;
        fi(0,3001){
            fj(0,3001){
                dp[i][j]=-1;
            }
        }
        dfs(0,0);
        build(0,0);
        cout<<out;
    }
    return 0;
}