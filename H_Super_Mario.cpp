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
string s;
struct Node{
    ll mxc[26];
    ll mxans[26][26];
    Node(){     //neutral node
        for(ll i=0;i<26;i++){
            mxc[i] = -1e18;
            for(ll j = 0; j < 26; j++){
                mxans[i][j] = -1e18;
            }
        }
    }
    Node(ll x, char c){
        for(ll i = 0; i < 26; i++){
            if(c - 'a' == i)
            mxc[i] = x;
            else mxc[i] = -1e18;
            for(ll j = 0; j < 26; j++){
                mxans[i][j] = -1e18;
            }
        }
    }
    void change(ll val);
};
struct segtree{ //0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln, Node &rn){
        Node ans = Node();
        for(ll i = 0; i < 26; i++){
            ans.mxc[i] = max(ln.mxc[i], rn.mxc[i]);
            for(ll j = 0; j < 26; j++){
                ans.mxans[i][j] = max({rn.mxans[i][j], ln.mxans[i][j], ll(ln.mxc[i] + rn.mxc[j])});
            }
        }
        return ans;
    }
    segtree(vector<ll> &arr){
        treesize = 1;
        while(treesize < arr.size()) treesize *= 2;
        segdata.assign(2*treesize, Node());
        for(ll i = 0; i < arr.size(); i++){
            segdata[treesize + i - 1] = Node(arr[i], s[i]);
        }
        for(ll i = treesize - 2; i >= 0; i--){
            segdata[i] = merge(segdata[2*i+1], segdata[2*i+2]);
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
using namespace std;
int main()
{
    HONDA
    int t = 1;
    cin >> t;
    while (t--)
    {
        ll n,q;cin>>n>>q;
        cin>>s;
        vll a(n);
        fi(0,n) cin>>a[i];
        segtree seg=segtree(a);
        while(q--){
            char a,b;cin>>a>>b;
            ll l,r;cin>>l>>r;
            l--;r--;
            Node m = seg.get(l,r+1,0,0,seg.treesize);
            if(m.mxans[a-'a'][b-'a'] < 0) cout<<-1<<endl;
            else cout<<m.mxans[a-'a'][b-'a']<<endl;
        }

    }
    return 0;
}
