#include <bits/stdc++.h> 
using namespace std;
#define ll long long
#define ld long double
#define all(a) a.begin(), a.end()
#define endl "\n"
#define Yara  ios::sync_with_stdio(0); cin.tie(0);
ll lcm(ll a, ll b) { return (a * b) / __gcd(a, b); }
int main()
{
    Yara
    ll t = 1 ;
   //cin >> t;
   next:
    while (t--)
    {
        ld x,y,n;
        cin>>x>>y>>n;
        ll x2=x;
        ll y2=y;
        if(y<=n) {
            cout<<x2/__gcd(x2,y2)<<"/"<<y2/__gcd(x2,y2)<<endl;
        }
        else {
            ld a1,a2,b;
            ld mn = 1e9;
            vector<pair<ll,ll>> mns;
            for(ll i=1;i<n+1;i++){
                b = i;
                a1 = floor((x*b)/y);
                a2 = a1 + 1;
                ld diff1 = fabs(x/y - a1/b);
                ld diff2 = fabs(x/y - a2/b);
                ll b3= b;
                ll a3 = a1;
                ll a4 = a2;
                if(diff1 < mn){
                    mns.clear();
                    mn = diff1;
                    mns.push_back({b3,a3});
                }
                else if(diff1 == mn){
                    mns.push_back({b3, a3});
                }
                if(diff2 < mn){
                    mns.clear();
                    mn = diff2;
                    mns.push_back({b3, a4});
                }
                else if(diff2 == mn){
                    mns.push_back({b3, a4});
                }
            }
            sort(all(mns));
            cout<<mns[0].second<<"/"<<mns[0].first;
        }
    }
    return 0;
}