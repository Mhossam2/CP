#include <bits/stdc++.h>
using namespace std;
#define HONDA                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
typedef long double ld;
typedef long long ll;
struct Node{
    ll best,pre,suf,len;
    Node(){
        best=pre=suf=0;
        len=1;
    }
    Node(ll val){
        len=1;
        if(val){ best=pre=suf=1; }
        else    { best=pre=suf=0; }
    }
    void change(ll val){
        if(val){ best=pre=suf=1; }
        else    { best=pre=suf=0; }
    }
};
struct segtree{
    ll treesize;
    vector<Node> segdata;
    Node merge(Node& ln, Node &rn){
        Node ans = Node();
        ans.len = ln.len+rn.len;
        ans.pre = ln.pre;
        if(ln.pre==ln.len) ans.pre+=rn.pre;
        ans.suf = rn.suf;
        if(rn.suf==rn.len) ans.suf+=ln.suf;
        ans.best = max({ln.best,rn.best,ln.suf+rn.pre});
        return ans;
    }
    segtree(vector<ll> &arr){
        treesize=1;
        while(treesize<arr.size()) treesize*=2;
        segdata.assign(2*treesize,Node());
        for(ll i =0;i< arr.size();i++){
            segdata[treesize + i -1] =Node(arr[i]);
        }
        for(ll i = treesize-2; i>=0 ;i--){
            segdata[i] = merge(segdata[2*i+1],segdata[2*i+2]);
        }
    }
    void update(ll ind, ll val, ll ni, ll lx, ll rx){
        if(rx - lx == 1){
            segdata[ni].change(val);
            return;
        }
        ll mid = (lx + rx)/2;
        if(ind < mid) update(ind, val, 2*ni+1, lx, mid);
        else update(ind, val, 2*ni+2, mid, rx);
        segdata[ni] = merge(segdata[2*ni+1], segdata[2*ni+2]);
    }
    Node get(ll l, ll r, ll ni, ll lx, ll rx){
        if(rx <= l || lx >= r) return Node();
        if(lx >= l && rx <= r) return segdata[ni];
        ll mid = (rx+lx)/2;
        Node ln = get(l, r, 2*ni+1, lx, mid);
        Node rn = get(l, r, 2*ni+2, mid, rx);
        return merge(ln, rn);
    }
};
int main(){
    ll n,q; cin >> n >> q;
    vector<ll> a(n+1,0);
    for(ll i=1; i<=n; i++) cin>>a[i];
    vector<vector<ll>> graph(n + 1);
    for(ll i = 0, u, v; i < n - 1; i++){
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<ll> tin(n + 1), tout(n + 1), vertex(n + 1), sz(n + 1, 1), d(n + 1, 1);
    ll timer = 0;
    function<ll(ll, ll)> euler =[&](ll u, ll p){
        tin[u] = ++timer;
        vertex[tin[u]] = u;
        for(auto v : graph[u]) if(v != p){
            d[v] = d[u] + 1;
            sz[u] += euler(v, u);
        }
        tout[u] = timer;
        return sz[u];
    };
    euler(1, -1);
    
    vector<ll> freq(2e5+5, 0);
    segtree seg = segtree(freq);

    auto add =[&](ll u){
        freq[a[u]]++;
        if(freq[a[u]]==1) seg.update(a[u],1,0,0,seg.treesize);
    };
    auto remove =[&](ll u){
        freq[a[u]]--;
        if(freq[a[u]]==0) seg.update(a[u],0,0,0,seg.treesize);
    };
    vector<vector<pair<pair<ll,ll>,ll>>> queries(n+1);
    for(ll i =0;i<q;i++){
        ll u,l,r;cin>>u>>l>>r;
        queries[u].push_back({{l,r},i});
    }
    vector<ll> ans(q);
    function<void(ll, ll, bool)> dfs =[&](ll u, ll p, bool keep){
        ll big = -1;
        for(auto v : graph[u]){
            if(v == p) continue;
            if(big == -1 || sz[v] > sz[big]) big = v;
        }
        for(auto v : graph[u]) 
            if(v != p && v != big) dfs(v, u, 0);
        if(big != -1) dfs(big, u, 1);
        for(auto v : graph[u]){
            if(v == p || v == big) continue;
            for(ll i = tin[v]; i <= tout[v]; i++){
                // here
                add(vertex[i]);
            }
        }
        add(u);
        for(auto [range,i]:queries[u]){
            ans[i]=seg.get(range.first,range.second+1,0,0,seg.treesize).best;
        }
        if(!keep){
            for(ll i = tin[u]; i <= tout[u]; i++) remove(vertex[i]);
        }
    };
    dfs(1, -1, 1);
    for(ll i:ans) cout<<i<<endl;
}