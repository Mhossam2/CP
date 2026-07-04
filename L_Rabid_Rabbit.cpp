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
const ll MOD = 1e9+7;
struct Node
{
    ll sm;
    Node()
    { // neutral node
        sm = 0;
    }
    Node(ll x)
    {
        sm = x;
    }
    void change(ll x)
    {
        sm += x;
    }
};
struct segtree
{ // 0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln, Node &rn)
    {
        Node ans = Node();
        ans.sm = ln.sm + rn.sm;
        return ans;
    }
    segtree(vector<ll> &arr)
    {
        treesize = 1;
        while (treesize < arr.size())
            treesize *= 2;
        segdata.assign(2 * treesize, Node());
        for (ll i = 0; i < arr.size(); i++)
        {
            segdata[treesize + i - 1] = Node(arr[i]);
        }
        for (ll i = treesize - 2; i >= 0; --i)
        {
            segdata[i] = merge(segdata[2 * i + 1], segdata[2 * i + 2]);
        }
    }
    void update(ll ind, ll val, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            segdata[ni].change(val);
            return;
        }
        ll mid = (lx + rx) / 2;
        if (ind < mid)
            update(ind, val, 2 * ni + 1, lx, mid);
        else
            update(ind, val, 2 * ni + 2, mid, rx);
        segdata[ni] = merge(segdata[2 * ni + 1], segdata[2 * ni + 2]);
    }
    Node get(ll l, ll r, ll ni, ll lx, ll rx)
    {
        if (rx <= l || lx >= r)
            return Node();
        if (lx >= l && rx <= r)
            return segdata[ni];
        ll mid = (rx + lx) / 2;
        Node ln = get(l, r, 2 * ni + 1, lx, mid);
        Node rn = get(l, r, 2 * ni + 2, mid, rx);
        return merge(ln, rn);
    }
};
using namespace std;
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        vll a(n);
        ll mx=0;
        fi(0,n) cin>>a[i];
        map<ll,vector<ll>> mp;
        fi(0,n){
            mx=max(mx,a[i]);
            mp[a[i]].push_back(i);
        }
        vll f;
        f.push_back(2);
        f.push_back(3);
        ll num1 = 2;
        ll num2 = 3;
        while(num2<= 2*mx){
            ll x = num2;
            num2+=num1;
            f.push_back(num2);
            num1=x;
        }
        vector<vector<ll>> pre(f.size(),vector<ll> (n,1e9));
        fi(0,f.size()){
            fj(0,n){
                ll tg = f[i] - a[j];
                if(mp.count(tg)==0) continue;
                auto it = upper_bound(all(mp[tg]), j);
                if(it==mp[tg].end()) continue;
                pre[i][j] = *it;
            }
        }
        vll z(n,0);
        vector<segtree> sg(f.size(), segtree(z));
        vector<pair<ll,pair<ll,ll>>> queries(q);
        fi(0,q){
            cin>>queries[i].first>>queries[i].second.first;
            queries[i].second.second=i;
        }
        ll ptr=0;
        sort(all(queries));
        reverse(all(queries));
        vector<ll> ans(q,0);
        for(ll i=n-1;i>=0;i--){
            for(ll j=0;j<f.size();j++){
                if(pre[j][i]==1e9) continue;
                sg[j].update(pre[j][i],1,0,0,sg[j].treesize);
            }
            while(ptr<q && i==queries[ptr].first){
                for(ll j=0;j<f.size();j++){
                    ans[queries[ptr].second.second] += ll(sg[j].get(queries[ptr].first,queries[ptr].second.first+1,0,0,sg[j].treesize).sm > 0);
                }
                ptr++;
            }
        }
        fi(0,q){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}
