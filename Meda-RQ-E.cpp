#include <bits/stdc++.h>
using namespace std;

#define HONDA                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
typedef vector<ll> vll;

struct Node
{
    ll mode, left, right;
    bool islazy;

    Node()
    {
        mode = 1;
        left = -1;
        right = -1;
        islazy = 0;
    }

    Node(ll x)
    {
        mode = 1;
        left = x;
        right = x;
        islazy = 0;
    }

    void update()
    {
        if (left == -1)
            return;

        left ^= 1;
        right ^= 1;
        islazy ^= 1;
    }
};

struct segtree
{
    ll treesize;
    vector<Node> segdata;

    Node merge(Node &ln, Node &rn)
    {
        if (ln.left == -1)
            return rn;

        if (rn.left == -1)
            return ln;

        Node ans;

        ans.left = ln.left;
        ans.right = rn.right;

        ans.mode = (ln.mode && rn.mode && (ln.right != rn.left));

        return ans;
    }

    segtree(vector<ll> &arr)
    {
        treesize = 1;

        while (treesize < arr.size())
            treesize <<= 1;

        segdata.assign(2 * treesize - 1, Node());

        // build leaves
        for (ll i = 0; i < arr.size(); i++)
        {
            segdata[treesize - 1 + i] = Node(arr[i]);
        }

        // build tree
        for (ll i = treesize - 2;; --i)
        {
            segdata[i] = merge(segdata[2 * i + 1], segdata[2 * i + 2]);

            if (i == 0)
                break;
        }
    }

    void propagate(ll ni, ll lx, ll rx)
    {
        if (!segdata[ni].islazy || rx - lx == 1)
            return;

        segdata[2 * ni + 1].update();
        segdata[2 * ni + 2].update();

        segdata[ni].islazy = 0;
    }

    void update_range(ll l, ll r, ll ni, ll lx, ll rx)
    {
        if (rx <= l || lx >= r)
            return;

        if (lx >= l && rx <= r)
        {
            segdata[ni].update();
            return;
        }

        propagate(ni, lx, rx);

        ll mid = (lx + rx) / 2;

        update_range(l, r, 2 * ni + 1, lx, mid);
        update_range(l, r, 2 * ni + 2, mid, rx);

        segdata[ni] = merge(segdata[2 * ni + 1], segdata[2 * ni + 2]);
    }

    Node get(ll l, ll r, ll ni, ll lx, ll rx)
    {
        if (rx <= l || lx >= r)
            return Node();

        propagate(ni, lx, rx);

        if (lx >= l && rx <= r)
            return segdata[ni];

        ll mid = (lx + rx) / 2;

        Node ln = get(l, r, 2 * ni + 1, lx, mid);
        Node rn = get(l, r, 2 * ni + 2, mid, rx);

        return merge(ln, rn);
    }
};

int main()
{
    HONDA

    ll n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vll a(n);

    for (ll i = 0; i < n; i++)
    {
        a[i] = (s[i] == '1');
    }

    segtree seg(a);

    while (q--)
    {
        ll type, l, r;
        cin >> type >> l >> r;

        l--;
        r--;

        if (type == 1)
        {
            seg.update_range(l, r + 1, 0, 0, seg.treesize);
        }
        else
        {
            cout << (seg.get(l, r + 1, 0, 0, seg.treesize).mode ? "Yes" : "No") << '\n';
        }
    }

    return 0;
}