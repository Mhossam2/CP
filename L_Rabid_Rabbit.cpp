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
const ll MOD = 1e9+7;
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        vll a(n);
        ll mx=0;
        fi(0,n) cin>>a[i];
        map<ll,vector<ll>> mp;
        fi(0,n){
            mx=max(mx,a[i]);
            mp[a[i]].push_back(i);
        }
        vll f;
        f.push_back(2);
        f.push_back(3);
        ll num1 = 2;
        ll num2 = 3;
        while(num2<= 2*mx){
            ll x = num2;
            num2+=num1;
            f.push_back(num2);
            num1=x;
        }
        vector<vector<int>> pre(f.size(),vector<int> (n,1e9));
        fi(0,f.size()){
            fj(0,n){
                ll tg = f[i] - a[j];
                if(mp.count(tg)==0) continue;
                auto it = upper_bound(all(mp[tg]), j);
                if(it==mp[tg].end()) continue;
                pre[i][j] = *it;
            }
        }
        vector<vector<int>> sufpre(f.size(),vector<int> (n,1e9));
        fi(0,f.size()){
            for(ll j=n-2;j>=0;j--){
                sufpre[i][j] = min(pre[i][j], sufpre[i][j+1]); 
            }
        }
        fi(0,q){
            ll l,r;cin>>l>>r;
            ll cnt = 0;
            fj(0,f.size()){
                if(sufpre[j][l]<=r) cnt++;
            }
            cout<<cnt<<endl;
        }
    }
    return 0;
}
