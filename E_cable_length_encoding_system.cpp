// رَبَّنَا آتِنَا مِن لَّدُنكَ رَحْمَةً وَهَيِّئْ لَنَا مِنْ أَمْرِنَا رَشَدًا

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define all(a) a.begin(), a.end()
#define endl "\n"
#define AMR                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);
ll lcm(ll a, ll b) { return (a * b) / __gcd(a, b); }
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
typedef unsigned __int128 bll;
const ll MOD = 1e9 + 7;
void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    string s1, s2;
    cin >> s1 >> s2;
    s1 = "0000"+s1;
    s2 = "0000" + s2;
    for (ll i = 0; i < s1.size() - 1; i++)
    {
        if (s1[i] == '1' && s1[i + 1] == '1')
        {
            s1[i] = '0';
            s1[i + 1] = '0';
            if (i - 1 < 0)
            {
                s1 = "0001" + s1;
            }
            else
            {
                s1[i - 1] = '1';
                i -= 3;
            }
        }
    }
    for (ll i = 0; i < s2.size() - 1; i++)
    {
        if (s2[i] == '1' && s2[i + 1] == '1')
        {
            s2[i] = '0';
            s2[i + 1] = '0';
            if (i - 1 < 0)
            {
                s2 = "0001" + s2;
            }
            else
            {
                s2[i - 1] = '1';
                i -= 3;
            }
        }
    }
    while (s2.size() < s1.size())
    {
        s2 = "0" + s2;
    }
    while (s1.size() < s2.size())
    {
        s1 = "0" + s1;
    }
    if (s1 < s2)
        cout << "<";
    else if (s1 == s2)
        cout << "=";
    else
        cout << ">";
}
int main()
{
    AMR

        ll tt = 1;
    // cin >> tt;
    while (tt--)
    {
        SOLVE();
    }
}