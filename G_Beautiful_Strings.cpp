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
        string s;cin>>s;
        vector<bool> a(s.size(),0);
        ll cnt =0;
        for(ll i=0;i<s.size();i++){
            if(a[i]) continue;
            if(i+1<s.size() && s[i]==s[i+1]){ a[i+1]=1; cnt++;}
            if(i+2<s.size() && s[i]==s[i+2]){ a[i+2]=1; cnt++;}
        }
        cout<<cnt<<endl;
    }
    return 0;
}
