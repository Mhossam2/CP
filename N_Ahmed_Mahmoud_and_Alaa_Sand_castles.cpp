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
        vll b=a;
        sort(all(b));
        mpll mp;
        ll ans=0;
        fi(0,n){
            mp[a[i]]++;
            mp[b[i]]--;
            if(!mp[a[i]]) mp.erase(a[i]);
            if(!mp[b[i]]) mp.erase(b[i]);
            if(mp.size()==0) ans++;
        }
        cout<<ans;
    }
    return 0;
}
