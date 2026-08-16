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
    // cin >> t;
    while (t--)
    {
        ll n,k,c;cin>>n>>k>>c;
        vll primes(k);
        fi(0,k) cin>>primes[i];
        mpll dist;
        deque<pair<ll,ll>> deq;
        deq.push_front({0,n});
        dist[n]=0;
        ll ans=-1;
        while(!deq.empty()){
            auto [d,val] = deq.front(); deq.pop_front();
            if(val==1){
                ans=d;
                break;
            }
            for(ll p:primes){
                if(val%p==0){
                    ll nval = val/p;
                    auto it = dist.find(nval);
                    if(it==dist.end() || dist[nval] > d){
                        dist[nval] = d;
                        deq.push_front({d,nval});
                    }
                }
            }
            ll nval = val-1;
            auto it = dist.find(nval);
            if(it==dist.end() || dist[nval] > d+c){
                dist[nval] = d+c;
                deq.push_back({d+c,nval});
            }
        }
        cout<<ans;
    }
    return 0;
}
