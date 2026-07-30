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
    //cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vll a(n);
        fi(0,n) cin>>a[i];
        ll ans = -1e18;
        for(ll i = 1; i < 11 && i <= n; i++){
            ll l=0;
            ll num = a[0];
            ll r = 1;
            while(r < n && r < i){
                num *= a[r];
                r++;
            }
            ans=max(num, ans);
            while(r<n){
                num *= a[r];
                num /= a[l];
                l++;
                r++;
                ans=max(num,ans);
            }
        }
        cout << ans;
    }
    return 0;
}
