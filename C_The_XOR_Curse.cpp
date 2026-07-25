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
    //cin >> t;
    while (t--)
    {
        ll n,k,x;cin>>n>>k>>x;
        vll a(n);
        ll mx=0;
        ll mn = 1e5;
        vector<ll> freq(1024,0);
        fi(0,n) cin>>a[i], freq[a[i]]++, mx=max(mx,a[i]), mn=min(mn,a[i]);
        ll ind=0;
        vector<ll> newfreq(1024,0);
        fi(0,k){
            ind=0;
            fj(0,1024) newfreq[j]=0;
            for(ll j = 0;j<1024;j++){
                ll newnum = j ^ x;
                if(ind%2 == 0){
                    newfreq[newnum] += freq[j]/2;
                    newfreq[j] += freq[j]/2 + 1;
                }
                else{
                    newfreq[newnum] += freq[j] / 2 + 1;
                    newfreq[j] += freq[j] / 2;
                }
                if(newfreq[newnum]) mx=max(mx,newnum), mn=min(mn,newnum);
                ind += freq[j];
            }
            freq=newfreq;
        }
        cout<<mx<<" "<<mn;
        
    }
    return 0;
}
