struct segment_tree
{
private:
    ll sz;
    vector<ll> seg;
    vector<ll> lazy; // added for lazy propagation

#define L 2 * node + 1
#define R 2 * node + 2
#define mid ((l + r) >> 1)

    ll base = 1e18; // the value doesn't effect on the segment tree  __ according to it's type
    ll lazy_base = 0; // the value indicating no pending updates __ according to it's type

    ll merge(ll x, ll y)
    { /////////////  type of seg  depend on (base value and merge )
        return min(x, y);
    }

    void apply(ll l, ll r, ll node, ll val)
    { /////////////  type of lazy depend on (lazy_base value and apply logic )
        if (val == lazy_base) return;
        
        // Example for Range Addition (with Min Segment Tree)
        seg[node] += val;  // Note: if seg was sum, this would be: seg[node] += val * (r - l + 1);
        lazy[node] += val;
    }

    void push(ll l, ll r, ll node)
    {
        if (lazy[node] == lazy_base || l == r)
            return;

        apply(l, mid, L, lazy[node]);         // push left
        apply(mid + 1, r, R, lazy[node]);     // push right

        lazy[node] = lazy_base;               // clear current node's lazy value
    }

    void build(ll l, ll r, ll node, vector<ll> &arr)
    {

        if (l == r)
        {
            if (l < arr.size())
            {
                seg[node] = arr[l];
            }
            return;
        }
        build(l, mid, L, arr);     // left
        build(mid + 1, r, R, arr); // right

        seg[node] = merge(seg[L], seg[R]);
    }

    void update(ll l, ll r, ll node, ll lq, ll rq, ll val)
    {
        if (r < lq || l > rq)
            return;

        if (lq <= l && rq >= r)
        {
            apply(l, r, node, val);
            return;
        }

        push(l, r, node); // push pending updates before going to children

        update(l, mid, L, lq, rq, val);         // left
        update(mid + 1, r, R, lq, rq, val);     // right
        
        seg[node] = merge(seg[L], seg[R]);
    }

    ll query(ll l, ll r, ll node, ll lq, ll rq)
    {

        if (r < lq || l > rq)
            return base;

        if (lq <= l && rq >= r)
            return seg[node];

        push(l, r, node); // push pending updates before visiting children

        ll left = query(l, mid, L, lq, rq);      // left
        ll right = query(mid + 1, r, R, lq, rq); // right

        return merge(left, right);
    }

public:
    segment_tree(vector<ll> &arr)
    {
        sz = 1;
        ll n = arr.size();
        while (sz < n)
            sz *= 2;

        seg = vector<ll>(sz * 2, base);
        lazy = vector<ll>(sz * 2, lazy_base); // initialize lazy array

        build(0, sz - 1, 0, arr);
    }

    void update(ll l, ll r, ll val) // updated to take a range [l, r]
    {
        update(0, sz - 1, 0, l, r, val);
    }

    ll query(ll l, ll r)
    {
        return query(0, sz - 1, 0, l, r);
    }

#undef R
#undef L
#undef mid
};