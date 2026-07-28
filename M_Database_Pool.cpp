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
        ll n,q;cin>>n>>q;
        set<pair<ll,ll>> s;
        mpll last;
        mpll dirty;
        ll clk=0;
        ll cnt=0;
        fi(0,q){
            ll op;cin>>op;
            if(op==1 || op==2){
                ll x;cin>>x;
                if(last.count(x)){
                    s.erase({last[x], x});
                    s.insert({clk, x});
                    last[x]=clk;
                }
                else{
                    if(s.size()>=n){
                        ll p = s.begin()->second;
                        s.erase(s.begin());
                        
                    }
                }
            }
        }
    }
    return 0;
}
