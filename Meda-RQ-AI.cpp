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
const ll MOD = 1e9 + 7;
struct Node
{
    ll mx;
    Node()
    { // neutral node
        mx = 0;
    }
    Node(ll x)
    {
        mx = x;
    }
    void change(ll x)
    {
        mx += x;
    }
};
struct segtree
{ // 0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln, Node &rn)
    {
        Node ans = Node();
        ans.mx = max(ln.mx , rn.mx);
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
    // cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        vll a(n);
        ll mn=1e18;
        fi(0,n){
            cin>>a[i];
            mn=min(mn,a[i]);
        }
        if(mn<0)
        fi(0,n){
            a[i]-=mn;
        }
        vector<ll> first(3e5,-1);
        vector<ll> last(3e5,-1);
        vll occ(3e5,0);
        fi(0,n){
            occ[a[i]]++;
            if(first[a[i]]==-1){
                first[a[i]]=i;
                if(i!=0){
                    last[a[i-1]]=i-1;
                }
            }
        }
        segtree seg(occ);
        while(q--){
            ll l,r;cin>>l>>r;
            l--;r--;
            if(a[l]==a[r]) cout<<r-l+1<<endl;
            else{
                ll ans = last[a[l]]-l + r-first[a[r]];
                ans += seg.get(last[a[l]],first[a[r]]+1,0,0,seg.treesize).mx;
                cout<<ans<<endl;
            }
        }
        
    }
    return 0;
}
