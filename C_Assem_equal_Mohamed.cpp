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
void dfs(ll u,ll p){
    
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vll a(n);
        vll b(n);
        fi(0,n) cin>>a[i];
        fi(0,n) cin>>b[i];
        bool ok=1;
        vector<ll> ans(n);
        ll cnt=0;
        fi(0,n){
            ans[i]=a[i];
            for(ll j = 0; j < 60;j++){
                if((b[i]&(1LL<<j))){
                    if((a[i]&(1LL<<j))==0){
                        ok=0;
                        break;
                    }
                }
                else{
                    if(a[i]&(1LL<<j)){
                        ans[i] -= (1LL<<j);
                    }
                }
            }
            if(!ok) break;
        }
        if(ok){
            cout<<"YES"<<endl;
            ll cnt=0;
            for(ll i=0;i<n;i++){
                if(a[i]!=ans[i]) cnt++;
            }
            cout<<cnt<<endl;
            for(ll i=0;i<n;i++){
                if(a[i]!=ans[i]) cout<<i+1<<" "<<ans[i]<<endl;
            }
        }
        else cout<<"NO"<<endl;
    }
    return 0;
}
