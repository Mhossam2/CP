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
struct Node{
    ll an,g;
    Node(){
        g=0;
        an=-1;
    }
    Node(ll x){
        an=g=x;
    }
    void change(ll x){
        an=g=x;
    }
};
struct segtree{
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln,Node &rn){
        Node ans = Node();
        ans.an = rn.an&ln.an;
        ans.g = __gcd(rn.g,ln.g);
        return ans;
    }
    segtree(vector<ll> &arr){
        treesize = 1;
        while(treesize<arr.size()) treesize*=2;
        segdata.assign(2*treesize, Node());
        for(ll i = 0;i<arr.size();i++){
            segdata[treesize+i-1] = Node(arr[i]);
        }
        for(ll i=treesize-2;i>=0;i--){
            segdata[i] = merge(segdata[2*i+1],segdata[2*i+2]);
        }
    }
    void update(ll ind,ll val, ll ni,ll lx,ll rx){
        if(rx-lx==1){
            segdata[ni].change(val);
            return;
        }
        ll mid = (lx+rx)/2;
        if(ind<mid) update(ind,val,2*ni+1,lx,mid);
        else update(ind, val, 2*ni+2,mid,rx);
        segdata[ni] = merge(segdata[2*ni+1],segdata[2*ni+2]);
    }
    Node get(ll l,ll r,ll ni,ll lx,ll rx){
        if(rx <= l || lx >= r) return Node();
        if(lx >= l && rx <= r) return segdata[ni];
        ll mid = (rx+lx)/2;
        Node ln = get(l, r, 2*ni+1, lx, mid);
        Node rn = get(l, r, 2*ni+2, mid, rx);
        return merge(ln, rn);
    }
};
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        vll a(n, 0);
        fi(0,n) cin>>a[i];
        segtree seg = segtree(a);
        while(q--){
            ll l,k; cin >> l >> k;
            ll lo = l - 1, hi = a.size() - 1;
            ll ans = 0;
            while (lo <= hi) {
                ll mid = lo + (hi - lo) / 2;
                Node num = seg.get(l - 1, mid + 1,0,0,seg.treesize);
                if ((num.an&k)==k && num.g>=k){
                    ans = mid - (l-1) +1;
                    lo = mid + 1;
                }
                else
                    hi = mid - 1;
            }
            cout<<ans<<" ";
        }

    }
    return 0;
}
