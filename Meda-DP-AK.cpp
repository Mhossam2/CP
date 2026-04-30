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
const int N = 1e6 + 5;
vector<vector<int>> divisors(N);
void sieve_divisors() {
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divisors[j].push_back(i);
        }
    }
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,k;cin>>n>>k;
        sieve_divisors();
        vll a(n);
        vector<int> freq(N,0);
        fi(0,n){
            cin>>a[i];
        }
        fi(0,n){
            auto &x = divisors[a[i]];
            fj(0,x.size()){
                //cout<<x[j]<<" ";
                freq[x[j]]++;
            }
            cout<<endl;
        }
        fi(0,n){
            int mx = 1;
            auto &x = divisors[a[i]];
            fj(0,x.size()){
                if(freq[x[j]]>=k) mx = max(mx, x[j]);
            }
            cout<<mx<<endl;
        }
    }
    return 0;
}