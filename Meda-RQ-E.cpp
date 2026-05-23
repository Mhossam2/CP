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
    ll mode, left, right;
    Node()
    { // neutral node
        mode = 1;
        left = -1;
        right = -1;
    }
    Node(ll x)
    {
        mode = 1;
        left = x;
        right = x;
    }
    void change()
    {
        left = 1 - left;
        right = 1 - right;
    }
};
struct segtree
{ // 0-indexed [l,r)
    ll treesize;
    vector<Node> segdata;
    Node merge(Node &ln, Node &rn)
    {
        Node ans = Node();
        if (ln.left == -1)
            return rn;
        if (rn.left == -1)
            return ln;
        if (ln.mode && rn.mode)
        {
            if (ln.right != rn.left)
            {
                ans.mode = 1;
            }
            else
                ans.mode = 0;
        }
        else
            ans.mode = 0;
        ans.left = ln.left;
        ans.right = rn.right;
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
    void update(ll ind, ll ni, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            segdata[ni].change();
            return;
        }
        ll mid = (lx + rx) / 2;
        if (ind < mid)
            update(ind, 2 * ni + 1, lx, mid);
        else
            update(ind, 2 * ni + 2, mid, rx);
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
        ll n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vll a(n, 0);
        fi(0, n)
        {
            a[i] = s[i] == '1';
        }
        segtree seg = segtree(a);
        while (q--)
        {
            ll type, l, r;
            cin >> type >> l >> r;
            l--;
            r--;
            if (type == 1)
            {   
                seg.update(l, 0, 0, seg.treesize);
                seg.update(r + 1, 0, 0, seg.treesize);
            }
            else
            {
                cout << (seg.get(l, r + 1, 0, 0, seg.treesize).mode ? "Yes" : "No") << endl;
            }
        }
    }
    return 0;
}