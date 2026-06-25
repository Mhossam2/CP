#include <bits/stdc++.h>
using namespace std;
#define HONDA ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long double ld;
typedef long long ll;
#define mpll  map<ll,ll>
#define vll vector<ll>
#define all(a) a.begin(), a.end()
#define fi(ii, n) for (ll i = ii; i < n; i++)
#define fj(jj, n) for (ll j = jj; j < n; j++)
#define fit(c) for(auto it = c.begin(); it != c.end(); ++it)
#define endl "\n"
int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};
inline bool in(int i, int j, int rows, int cols){
    return i>=0 && i<rows && j>=0 && j<cols;
}
inline bool in(int i, int l, int h){
    return i >= l && i <= h;
}
using namespace std;
int main() {
    HONDA
    int t = 1;
    cin >> t;
    while(t--){
        ll n,m;cin>>n>>m;
        ll x=0;
        vll a;
        fi(0,m){
            ll num;cin>>num;
            x ^= num;
            a.push_back(num);
        }
        if((n-m)==0) cout<<x<<endl;
        else if(((n-m)%3)==1) cout << (x ^ a[m-1] ^ a[m-2])<<endl;
        else if(((n-m)%3)==2) cout << (x ^ a[m-1])<<endl;
        else cout<< (x ^ a[m-2])<<endl;
    }
    return 0;
}
