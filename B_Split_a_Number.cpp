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
string string_addition(const string &s1, const string &s2)
{
    string res = "";
    ll carry = 0;
    ll n1 = s1.size();
    ll n2 = s2.size();
    ll i = n1 - 1;
    ll j = n2 - 1;
    while (i >= 0 || j >= 0 || carry)
    {
        ll digit1 = (i >= 0) ? s1[i] - '0' : 0;
        ll digit2 = (j >= 0) ? s2[j] - '0' : 0;
        ll sum = digit1 + digit2 + carry;
        res.push_back((sum % 10) + '0');
        carry = sum / 10;
        i--;
        j--;
    }
    reverse(res.begin(), res.end());
    return res;
}
bool smaller(const string &a, const string &b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    return a < b;
}
int main()
{
    HONDA
    int t = 1;
    // cin >> t;
    while (t--)
    {
        ll n;
        string s;
        cin >> n >> s;
        string ans = "";
        for (ll i = 0; i <= 1e6; i++)
            ans += "9";
        ll indf = n / 2 + 1;
        ll indb = n / 2;
        while (s[indf] == '0')
        {
            indf++;
        }
        while (s[indb] == '0')
        {
            indb--;
        }
        if (indf < n)
        {
            string s1 = s.substr(0, indf);
            string s2 = (s.substr(indf));
            string sum = string_addition(s1, s2);
            if (smaller(sum, ans))
            {
                ans = sum;
            }
        }
        if (indb > 0)
        {
            string s1 = s.substr(0, indb);
            string s2 = (s.substr(indb));
            string sum = string_addition(s1, s2);
            if (smaller(sum, ans))
            {
                ans = sum;
            }
        }
        // cout << indf << " " << indb << endl;
        cout << ans << endl;
    }
    return 0;
}
