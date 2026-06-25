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
        ll n,d;cin>>n>>d;
        vll last(n,-1);
        ll num = 0;
        bool found1 =0; bool found2=0;
        ll num1=-1;ll num2=-1; 
        fi(1,n+1){
            num = (num * 10 + d)%n;
            if(num%n==0){
                found1=1;
                num1=i;
                break;
            }
            if(last[num]!=-1){
                found2=1;
                num1=last[num]; num2=i;
                break;
            }
            last[num]=i;
        }
        if(found1){
            fi(0,num1){
                cout<<d;
            }
        }
        if(found2){
            fi(0,num2-num1) cout<<d;
            fi(0,num1) cout<<0;
        }
        cout<<endl;
    }
    return 0;
}
