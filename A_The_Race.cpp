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
    ll num;
    Node(){
        num=0;
    }
    Node(ll x){
        num=x;
    }
    void change(ll x){
        num+=x;
    }
};
struct segtree{
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln,Node &rn){
        Node ans = Node();
        ans.num = rn.num+ln.num;
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
        ll n;cin>>n;
        vector<pair<ll,ll>> a(n);
        for(ll i=0;i<n;i++){
            ll p,q,r1,r2;cin>>p>>q>>r1>>r2;
            ll x = (p*r1+q)/(r1-r2);
            ll v = (p*r2+q)/(r2-r1);
            a[i]={x,v};
        }
        sort(all(a));
        vector<ll> vs(n);
        for(ll i=0;i<n;i++) vs[i] = a[i].second;
        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());
        ll m=vs.size();
        vll zeros(n,0);
        segtree seg = segtree(zeros);
        ll cnt=0;
        for(ll i = 0; i < n;i++){
            ll ind = (lower_bound(vs.begin(),vs.end(), a[i].second)-vs.begin());
            ll num = seg.get(0,ind+1,0,0,seg.treesize).num;
            cnt += i-num;
            seg.update(ind,1,0,0,seg.treesize);
        }
        cout<<cnt<<endl;
    }
    return 0;
}
