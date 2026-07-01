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
ll k;
bool check(ll mid, vector<pair<ll,ll>> &a){
    ll last=-1e9;
    ll cnt=0;
    for(auto &p : a){
        if(p.second - last >= mid){
            cnt++;
            last=p.first;
            if(cnt>=k) return true;
        }
    }
    return cnt >= k;
}
ll bn(vector<pair<ll,ll>> &a){
    ll lo = 1, hi = 1e18;
    ll ans = -1;
    while(lo < hi){
        ll mid = lo + (hi - lo + 1) / 2;
        if(check(mid,a)){
            lo = mid;
            ans = mid;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n;cin>>n>>k;
        vector<pair<ll,ll>> a(n);
        fi(0,n){
            cin>>a[i].second>>a[i].first;
        }
        sort(all(a));
        cout<<bn(a);
    }
    return 0;
}
