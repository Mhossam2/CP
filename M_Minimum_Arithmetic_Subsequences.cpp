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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

////////////////////////Seg tree (merge sort tree, PBDS ordered set - updatable)////////////////////////////////
// encode (value, unique tiebreaker) so duplicates don't collide in the set
typedef pair<ll,ll> pll;
typedef tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update> ordset;

// Full complexity summary
// Operation	Cost
// Build	O(n log² n)
// Point update	O(log² n)
// countLE(l, r, x)	O(log² n)
// k-th smallest in [l,r)	O(log³ n) (binary search over countLE)
// Memory	O(n log n) total across all nodes

struct Node{
    ordset vals;
    Node(){}    //neutral node (empty)
};
struct segtree{ //0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    vector<ll> arr; // keep original array to know current value at each index

    void insertAt(ll ni, ll val, ll idx){
        segdata[ni].vals.insert({val, idx});
    }
    void eraseAt(ll ni, ll val, ll idx){
        segdata[ni].vals.erase({val, idx});
    }

    segtree(vector<ll> &a){
        arr = a;
        treesize = 1;
        while(treesize < arr.size()) treesize *= 2;
        segdata.assign(2*treesize, Node());
        for(ll i = 0; i < (ll)arr.size(); i++){
            ll ni = treesize + i - 1, lx = i, rx = i+1;
            // walk up inserting into every ancestor
            ll cur = ni;
            insertAt(cur, arr[i], i);
            while(cur != 0){
                cur = (cur - 1) / 2;
                insertAt(cur, arr[i], i);
            }
        }
    }

    // point update: set index ind to newVal
    void update(ll ind, ll newVal){
        ll ni = treesize + ind - 1;
        ll oldVal = arr[ind];
        arr[ind] = newVal;
        eraseAt(ni, oldVal, ind);
        insertAt(ni, newVal, ind);
        ll cur = ni;
        while(cur != 0){
            cur = (cur - 1) / 2;
            eraseAt(cur, oldVal, ind);
            insertAt(cur, newVal, ind);
        }
    }

    // count elements <= x in [l, r), O(log^2 n)
    ll countLE(ll l, ll r, ll x, ll ni, ll lx, ll rx){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r){
            return segdata[ni].vals.order_of_key({x, (ll)2e18});
        }
        ll mid = (rx+lx)/2;
        return countLE(l, r, x, 2*ni+1, lx, mid) + countLE(l, r, x, 2*ni+2, mid, rx);
    }
};
int main()
{
    HONDA
    int t = 1;
    //cin >> t;
    while (t--)
    {
        ll n;cin>>n;
    }
    return 0;
}
