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
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll a,m,n;cin>>a>>n>>m;
        vector<pair<ll,ll>> seg(n);
        vector<pair<ll,ll>> s(m);
        fi(0,n){
            ll l,r;cin>>l>>r;
            seg[i]={l,r};
        }
        fi(0,m){
            ll x,y;cin>>x>>y;
            s[i] = {x,y};
        }
        sort(all(s));
        for(ll i=0;i<seg.size();i++){
            for(ll j=0;j < m;j++){
                if(s[j].first >= seg[i].first && s[j].first < seg[i].second){
                    ll temp = seg[i].second;
                    seg[i].second = s[j].first;
                    seg.push_back({s[j].first + 1, temp});
                }
            }
        }
        sort(all(seg));
        ll ans = 0;
        ll x = 0;
        for(ll i = 0; i < seg.size(); i++){
            ll mn = 1e9;
            ll temp=-1;
            for(ll j = 0;j<m;j++){
                if(s[j].first <= seg[i].first){
                    ll cost = (seg[i].second - s[j].first) * s[j].second;
                    if(cost < mn){
                        mn = cost;
                        temp = j;
                    }
                }
            }
            if(mn==1e9){
                x=1;
                break;
            }
            s[temp].first=seg[i].second;
            ans+=mn;
        }
        if(x==1) cout<<-1<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}