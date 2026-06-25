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
    //cin >> t;
    while(t--){
        ld a,b,c,x,y,z;cin>>a>>b>>c>>x>>y>>z;
        ld arr[6][3] = {{x,y,z},{x,z,y},{z,x,y},{z,y,x},{y,x,z},{y,z,x}};
        bool f=false;
        fi(0,6){
            if(a/arr[i][0] == b/arr[i][1] && a/arr[i][0] == c/arr[i][2]){
                cout<<"YES";
                f=1;
            }
        }
        if(!f) cout<<"NO";
    }
    return 0;
}
