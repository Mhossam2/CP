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
const ld pi = acos(-1);

void SOLVE() //                        بِسْمِ اللَّهِ الرَّحْمَنِ الرَّحِيمِ
{
    ll n, m, k;
    cin >> n >> m >> k;

    vector<pair<ll, ll>> a(m);

    for (auto &[x, y] : a)
        cin >> x >> y;

    sort(all(a));

    vector<ll> patern(k);

    ll x = 0 ; 
    for (ll i = 1 ; i <= k - 1 ; i++)
    {
        patern[i-1] = i ;
        x ^= i ; 
    }
    if(x == 0 || x <= (k -1) )
    {
ll msb = (1LL << 20);
        patern[k - 1] = msb + x;
        
        if (x == 1 && k > 2) {
            patern[1] += msb;
        } else {
            patern[0] += msb;
        }
    }
    else
    {
        patern[k-1] = x ;
    }


    sort(all(patern)) ; 
   //for(ll i : patern)cout << i << ' ' ; 
    vector<ll> ans(n , -1) ; 
    ll L= -1 , R = -1 ;  
    for(auto &[l,r] : a) 
    {
         ll mx = l-1 ;
        if(L == -1 || (mx-1 < 0 || ans[mx-1] == -1 ))
        {
            ll idx = 0; 
            for(ll i = l-1 ; i <= r-1 ; i ++ )ans[i] = patern[idx%k] , idx ++ ;
        }
        else
        {
            auto it = lower_bound(all(patern) , ans[mx-1]) ; 

            ll idx = (it - patern.begin());
            idx ++ ;
            for(ll i = l-1 ; i <= r-1 ; i ++ )
            {
                ans[i] = patern[idx%(k)];
                idx ++ ; 
            }
        }
        L = l ;
        R = r ; 
    }

    for(ll i : ans)
    {
        if(i == -1)i = 1 ; 
        cout << i << ' ' ;
    }
    cout << endl ; 
}

int main()
{
    AMR

        ll tt = 1;
    cin >> tt;
    while (tt--)
    {
        SOLVE();
    }
}