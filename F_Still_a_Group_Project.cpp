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
      vll a2(n),b2(n);
      map<ll,set<ll>> mp;
      fi(0,n){
        cin>>a2[i];
        mp[a2[i]].insert(i);
      }
      bool found;
      bool x=0;
      fi(0,n){
        ll num;cin>>num;
        found = 0;
        fit(mp[num]){
            if((*it - i)%m==0){
                mp[num].erase(*it);
                found=1;
                break;
            }
        }
        if(!found) x=1;
      }
      if(x) cout<<"No"<<endl;
      else cout<<"Yes"<<endl;
    }
    return 0;
}
