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
    ll n, x, y;
    cin >> n >> x >> y;

    string zz;
    cin >> zz;

    string dir;
    cin >> dir;

    ll d = (dir == "tail" ? 1 : -1);

    string s;
    cin >> s;


    for (ll i = 0; i < s.size(); i++)
    {
        if (y == 1 && d == -1)
        {
            d = 1;
        }

        if (y == n && d == 1)
        {
            d = -1;
        }

        if (s[i] == '0')
        {
            if (d == 1 )
            {
                if(x > y){
                    if(x != n )x ++ ; 
                }else{
                    if(x != 1 )x -- ; 
                }
            }else{
                if(x < y ){
                    if(x != 1 )x -- ; 
                }else{
                    if(x != n )x ++ ;
                }
            }
            if (x == y)
            {
                cout << "Controller ";
                cout << i + 1;
                return;
            }
            y += d;

            if (y == x)
            {
                cout << "Controller ";
                cout << i + 1;
                return;
            }
        }
        else
        {
            ll dff_h = 1e18, dff_t = 1e18;
            if (d == 1)
            {
                dff_h = min(dff_h, n - y);
                dff_t = min(dff_h, 2 * n - 1 - y);
            }
            else
            {
                dff_h = min(dff_h, y - (1 - n));
                dff_t = min(dff_h, y - 1);
            }

            if (dff_h > dff_t)
            {
                x = n;
            }
            else
            {
                x = 1;
            }
            y += d;

            if (y == x)
            {
                cout << "Controller ";
                cout << i + 1;
                return;
            }
        }
       // cout << x << ' ' << y << endl ; 
    }

    cout << "Stowaway";
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