#include <bits/stdc++.h>
using namespace std;
#define HONDA ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long double ld;
typedef long long ll;
#define mpll  map<ll,ll>
#define vll vector<ll>
#define all(a) a.begin(), a.end()
#define fi(ii, n) for (ll i = ii; i < n; i++)
#define fj(jj, n) for (ll j = jj; j < n; j++)
#define fit(c) for(auto it = c.begin(); it != c.end(); ++it)
#define endl "\n"
int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};
inline bool in(int i, int j, int rows, int cols){
    return i>=0 && i<rows && j>=0 && j<cols;
}
inline bool in(int i, int l, int h){
    return i >= l && i <= h;
}
struct Node{
    ll mn;
    Node(){
        mn = 1e18;
    }
    void change(ll x){
        mn = x;
    }
};
struct segtree{
    ll treesize;
    vector<Node> segdata;

    segtree(ll n){
        treesize=1;

        while(treesize < n) treesize *= 2;

        segdata.assign(2*treesize, Node());

    }

    Node merge(Node &ln, Node &rn){
        Node ans = Node();
        ans.mn = min(ln.mn , rn.mn);
        return ans;
    }

    void set(ll ind, ll val, ll ni, ll lx, ll rx){
        if(rx - lx == 1){
            segdata[ni].change(val);
            return;
        }
        ll mid = (lx + rx)/2;
        if(ind < mid){
            set(ind, val, 2*ni+1, lx, mid);
        }
        else{
            set(ind, val, 2*ni+2, mid, rx);
        }
        segdata[ni] = merge(segdata[2*ni+1], segdata[2*ni+2]);
    }

    void set(ll ind, ll val){
        set(ind, val, 0, 0, treesize);
    }

    Node get(ll l, ll r, ll ni, ll lx, ll rx){
        if(rx <= l || lx >= r) return Node();
        if(lx >= l && rx <= r) return segdata[ni];
        
        int mid=(rx+lx)/2;
        Node ln = get(l, r, 2*ni+1, lx, mid);
        Node rn = get(l, r, 2*ni+2, mid, rx);
        return merge(ln, rn);
    }

    ll get(ll l,ll r){
        return get(l, r, 0, 0, treesize).mn;
    }
    ll find(ll num, ll l, ll r, ll ni,ll lx,ll rx){
        if(rx <= l || lx >= r) return -1;
        if(segdata[ni].mn > num) return -1;
        if(rx-lx==1) return lx;
        ll mid = (rx+lx)/2;
        ll res = find(num,l,r,2*ni+1,lx,mid);
        if(res!=-1) return res;
        return find(num,l,r,2*ni+2,mid,rx);
    }
    ll find(ll num,ll l, ll r){
        return find(num,l,r,0,0,treesize);
    }
};
using namespace std;
int main() {
    HONDA
    int t = 1;
    //cin >> t;
    while(t--){
		ll n,m; cin>>n>>m;
        vector<ll> a(n);
		segtree sg = segtree(n);
        fi(0,n){
            cin>>a[i];
            sg.set(i, a[i]);
        }
		fi(0,m){
			ll x,l,r;cin>>x>>l>>r;
            while(true){
                ll res = sg.find(x, l-1, r);
                if(res==-1) break;
                x %= a[res];
            }
            cout<<x<<endl;
		}
    }
    return 0;
}
