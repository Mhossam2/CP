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
ll n,k,c;
vll tt,m;
bool check(ll num){
    ll pos = 0;
    ll cnt = 0;
    while(pos < n){
        ll r = pos;
        ll sm=0;
        ll mx=0;
        while(r<n){
            ll nsm = sm + tt[r];
            ll nmx = max(mx,m[r]);
            if(nsm+c*nmx<=num){
                sm =nsm;
                mx=nmx;
                r++;
            }
            else break;
        }
        if(r==pos || cnt+1 > k) return false;
        cnt++;
        pos = r;
    }
    return true;
}
ll bn(){
    ll lo = 0, hi = 1e18;
    ll ans = -1;
    while(lo <= hi){
        ll mid = lo + (hi - lo) / 2;
        if(check(mid)){
            hi = mid - 1;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        cin>>n>>k>>c;
        tt.clear();
        m.clear();
        fi(0,n){
            ll x,y;cin>>x>>y;
            tt.push_back(x);
            m.push_back(y);
        }
        cout<<bn()<<endl;
    }
    return 0;
}
