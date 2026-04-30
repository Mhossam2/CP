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
        ll n;cin>>n;
        ll cnt0=0;ll cnt1=0;
        vll near1(n,-1),near0(n,-1);
        ll lst1=-1;ll lst0=-1;
        for(ll i=n-1;i>=0;i--){
            if(s[i]=='0') lst0=i;
            if(s)
        }
    }
    return 0;
}