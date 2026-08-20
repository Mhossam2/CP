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
using cd = complex<ld>;
const ld PI = acos(-1);
void fft(vector<cd> & a, bool invert) {
    ll n = a.size();

    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b, ll cap = -1) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < (ll)a.size() + (ll)b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    ll sz = n;
    if (cap >= 0)                 
        sz = min(n, cap + 1);
    
    vector<ll> result(sz);
    for (ll i = 0; i < sz; i++)
        result[i] = llround(fa[i].real());
    return result;
}

vector<ll> poly_pow(vector<ll> p, ll k, ll cap){
    for (auto &x : p) x = (x > 0) ? 1 : 0;
    vector<ll> ans{1};
    while (k){
        if (k & 1){
            ans = multiply(ans, p, cap);
            for (auto &x : ans) x = (x > 0) ? 1 : 0;
        }
        p = multiply(p, p, cap);
        for (auto &x : p) x = (x > 0) ? 1 : 0;
        k >>= 1;
    }
    return ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        string s;cin>>s;
        ll n=s.size();
        vll a(n,0);
        vll b(n,0);
        fi(0,n){
            if(s[i]=='A') a[i]=1;
            else b[i]=1;
        }
        reverse(all(a));
        vll conv = multiply(a,b);
        fi(1,n){
            cout<<conv[n-1-i]<<endl;
        }
    }
    return 0;
}
