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
ll phi(ll n){
    ll res =n; 
    for(ll p=2;p * p <=n;p++) 
    if (n%p==0){ 
        while(n%p==0)
        n/=p; 
        res-=res/ p; 
    } 
    if(n>1)
    res-=res/n; 
    return res; 
} 
vector<ll>phi_all,mu_all; 
void phi_mobius_sieve(ll n)
{
    phi_all.resize(n+1); 
    mu_all.assign(n+1,1); 
    for(ll i=0;i<=n;i++)
    phi_all[i]=i; 
    for(int i=2;i<=n;i++){
        if (phi_all[i]==i){ 
            for(int j=i;j<=n;j+=i){ 
                phi_all[j]-=phi_all[j]/i; 
                mu_all[j]=-mu_all[j]; 
            } 
            for(ll j=1LL*i*i;j<=n;j+=1LL*i*i)
            mu_all[j]=0; 
        } 
    } 
    mu_all[0]=0;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n,x;cin>>n>>x;
        vector<ll> cnt(1001, 0);
        fi(0,n){
            ll x;cin>>x;
            cnt[x]++;
        }
        ll mx = 1e6/x;
        vector<

    }
    return 0;
}
