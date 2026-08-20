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
using cd = complex<double>;
const double PI = acos(-1);
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
    vector<ll> ans{1};
    while (k){
        if (k & 1){
            ans = multiply(ans, p, cap);
        }
        k >>= 1;
        if(k) p = multiply(p, p, cap);
    }
    return ans;
}
string mul_two_big_int(const string &s1, const string &s2) {
    ll n = s1.size(), m = s2.size();

    vector<ll> poly1(n), poly2(m);
    for (ll i = 0; i < n; ++i) {
        poly1[n-i-1] = s1[i] - '0';
    }

    for (ll i = 0; i < m; ++i) {
        poly2[m-i-1] = s2[i] - '0';
    }

    vector<ll> ans = multiply(poly1, poly2);
    ll k = ans.size();

    for (ll i = 0; i < k - 1; ++i) {
        ans[i + 1] += ans[i] / 10;
        ans[i] = ans[i] % 10;
    }

    string final = to_string(ans[k - 1]);
    for (ll i = k - 2; i >= 0; --i) {
        final += (char)(ans[i] + '0');
    }

    for (ll i = 0; i < k; ++i) {
        if(final[i] != '0') return final.substr(i);
    }
    return "0";
}

string power_of_big_int(string s, ll p) {
    string ans = "1";
    while (p) {
        if(p&1) ans = mul_two_big_int(ans, s);
        s = mul_two_big_int(s, s);
        p >>= 1;
    }
    return ans;
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll OFF =0;
        ll n;cin>>n;
        set<ll> s;
        vll val(n,0);
        fi(0,n){
            cin>>val[i];
            s.insert(val[i]);
            ll OFF=max(OFF,val[i]);
        }
        if(s.size()<n){
            cout<<0<<endl;
            continue;
        }
        vll a(OFF + 1, 0);
        fi(0,n){
            a[val[i]] = 1;
        }
        vll b = a;
        reverse(all(b));
        vll ans = multiply(a,b);
        fi(1,ans.size()){
            if(ans[i]) cout<<i-OFF<<endl;
        }
    }
    return 0;
}
