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
    string a,b;cin>>a>>b;
    ll n;cin>>n;
    map<ll,ll> mpa,mph;
    for(ll i=0;i<n;i++){
        ll time,key;
        char c,val;
        cin>>time>>c>>key>>val;
        if(c=='h'){
            mpa[key]++;
            if(val=='r') mpa[key]++;
            if(mpa[key]==2 || mpa[key]==3){
               cout<<a<<" "<<key<<" "<<time<<endl;
               mpa[key]=1e9; 
            }
        }
        else{
            mph[key]++;
            if(val=='r') mph[key]++;
            if(mph[key]==2 || mph[key]==3){
               cout<<b<<" "<<key<<" "<<time<<endl;
               mph[key]=1e9; 
            }
        }
    }
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