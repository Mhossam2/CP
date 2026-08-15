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
        if(val) best=pre=suf=0;
    }
    void change(ll val){
        if(val) best=pre=suf=0;
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