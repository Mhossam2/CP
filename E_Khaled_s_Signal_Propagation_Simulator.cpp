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
     cin >> t;
    while (t--)
    {
        ll n,m;cin>>n>>m;
        string s;cin>>s;
        vector<ll> a(n), a2(n);
        for (ll i = 0; i < n; i++) a[i] = s[i] - '0';
        for(ll i=0; i<m;i++){
            a2 = a;
            for(ll j=0; j<n;j++){
                if(a[j] == 0){
                    ll cnt = 0;
                    if(j > 0 && a[j-1] == 1) cnt++;
                    if(j < n-1 && a[j+1] == 1) cnt++;
                    if(cnt == 1){
                        a2[j] = 1;
                    }
                }
            }
            if(a2==a) break;
            a=a2;
        }
        fi(0,n) cout<<a[i];
        cout<<endl;
    }
    return 0;
}