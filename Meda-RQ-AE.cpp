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
        ll n,q; cin >> n >> q;
        vll a(n, 0);
        segtree seg(a);
        fi(0,n){
            cin>>a[i];
        }
        vector<ll> b = a;
        mpll mp;
        sort(all(b));
        fi(0,n){
            if(mp[b[i]]==0) mp[b[i]]=i;
        }
        fi(0,n){
            a[i]=mp[a[i]];
        }
        vector<pair<ll,pair<ll,ll>>> queries(q);
        fi(0,q){
            cin>>queries[i].second.first>>queries[i].first;
            queries[i].second.second=i;
        }
        sort(all(queries));
        ll cur = 0;
        mpll last;
        vector<ll> ans(q);
        for(auto &p : queries){
            while(cur <= p.first-1){
                if(last.count(a[cur])){
                    seg.update(last[a[cur]], 0 ,0,0,seg.treesize);
                }
                seg.update(cur,1,0,0,seg.treesize);
                last[a[cur]]=cur;
                cur++;
            }
            ans[p.second.second] = seg.get(p.second.first-1, p.first,0,0,seg.treesize).sm;
        }
        fi(0,q) cout<<ans[i]<<endl;
    }
    return 0;
}
