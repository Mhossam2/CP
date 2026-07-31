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
    cin >> t;
    while (t--)
    {
        ll n;cin>>n;
        vll a(n);
        fi(0,n) cin>>a[i];
        vll newarr(n-1);
        fi(0,n-1){
            newarr[i] = a[i]^a[i+1];
        }
        fi(0,n-1) cout<<newarr[i]<<" ";
        cout<<endl;
        ll ans = 1;
        mpll freq;
        fi(1,n){
            if(a[i]==a[i-1]) continue;
            ll b=0;
            for(ll j=0;j<=30;j++){
                if((a[i-1]&(1LL<<j)) != (a[i]&(1LL<<j))) b=j;
            }
            if(freq.count(b)){
                if(freq[b]!=(a[i-1]&(1LL<<b))){
                    ans++;
                    freq.clear();
                    freq[b]=a[i-1]&(1LL<<b);
                }
            }
            else{
                freq[b]=a[i-1]&(1LL<<b);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
