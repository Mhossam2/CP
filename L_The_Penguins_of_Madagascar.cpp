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
bool check(ll num, vector<ll> &a){
    ll g=0;
    fi(0,a.size()){
        g = gcd(a[i],g);
        if(g==num) g = 0;
    }
    return (g == 0);
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vll a(n);
        fi(0,n) cin>>a[i];
        ll l = 0, r = 2e9;
        ll ans=1;
        while (l <= r) {
            ll mid = l + (r - l) / 2;

            if (check(mid,a)){
                ans=mid;
                l=mid+1;
            }
            else
                r = mid - 1;
        }
        cout<<ans<<endl;
    }
    return 0;
}
