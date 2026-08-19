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
        ld ang = 2 * PI / len * (invert ? -1 : 1);
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

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
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

    vector<ll> result(n);
    for (ll i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
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
struct BigFloat {
    string digits;   // leading digits, most-significant first, no leading zeros
    ll totalDigits;  // TRUE digit count of the exact value
    // true value ≈ digits followed by (totalDigits - digits.size()) unknown digits
};

BigFloat toBigFloat(const string &s, ll precision) {
    BigFloat r;
    r.totalDigits = s.size();
    r.digits = (ll)s.size() > precision ? s.substr(0, precision) : s;
    return r;
}

BigFloat mulBigFloat(const BigFloat &a, const BigFloat &b, ll precision) {
    string prod = mul_two_big_int(a.digits, b.digits); // exact, mantissas are bounded size
    ll za = a.totalDigits - (ll)a.digits.size(); // digits dropped from a
    ll zb = b.totalDigits - (ll)b.digits.size(); // digits dropped from b

    BigFloat r;
    r.totalDigits = (ll)prod.size() + za + zb;
    r.digits = (ll)prod.size() > precision ? prod.substr(0, precision) : prod;
    return r;
}

// returns {first `limit` digits of s^p, true total digit count of s^p}
pair<string, ll> power_leading_digits(string s, ll p, ll limit, ll guard = 50) {
    ll precision = limit + guard;
    BigFloat ans  = toBigFloat("1", precision);
    BigFloat base = toBigFloat(s, precision);

    while (p) {
        if (p & 1) ans = mulBigFloat(ans, base, precision);
        base = mulBigFloat(base, base, precision);
        p >>= 1;
    }

    string res = (ll)ans.digits.size() > limit ? ans.digits.substr(0, limit) : ans.digits;
    return {res, ans.totalDigits};
}
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        string s1,s2;cin>>s1>>s2;
        auto [s,num] = mulBigFloat(toBigFloat(s1,1e5),toBigFloat(s2,1e5),1e5);
        cout<<s<<endl;
    }
    return 0;
}
