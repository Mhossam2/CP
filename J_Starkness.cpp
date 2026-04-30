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


struct pt {
    ll x, y;
    pt() {}
    pt(ll x_, ll y_) : x(x_), y(y_) {}
    void read() {
        cin >> x >> y;
    }
};

bool operator==(const pt& a, const pt& b) {
    return a.x == b.x and a.y == b.y;
}


struct CustomHashPoint {
    size_t operator()(const pt& p) const {
        static const uint64_t C = chrono::steady_clock::now().time_since_epoch().count();
        return C ^ ((p.x << 32) ^ p.y);
    }
};


ll dist2(pt a, pt b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx*dx + dy*dy;
}


pair<int,int> closest_pair_of_points(vector<pt> P) {
    int n = int(P.size());
    assert(n >= 2);

    // if there is a duplicated point, we have the solution
    unordered_map<pt,int,CustomHashPoint> previous;
    for (int i = 0; i < int(P.size()); ++i) {
        auto it = previous.find(P[i]);
        if (it != previous.end()) {
            return {it->second, i};
        }
        previous[P[i]] = i;
    }

    unordered_map<pt,vector<int>,CustomHashPoint> grid;
    grid.reserve(n);

    mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dis(0, n-1);

    ll d2 = dist2(P[0], P[1]);
    pair<int,int> closest = {0, 1};

    auto candidate_closest = [&](int i, int j) -> void {
        ll ab2 = dist2(P[i], P[j]);
        if (ab2 < d2) {
            d2 = ab2;
            closest = {i, j};
        }
    };

    for (int i = 0; i < n; ++i) {
        int j = dis(rd);
        int k = dis(rd);
        while (j == k) k = dis(rd);
        candidate_closest(j, k);
    }

    ll d = ll( sqrt(ld(d2)) + 1 );

    for (int i = 0; i < n; ++i) {
        grid[{P[i].x/d, P[i].y/d}].push_back(i);
    }

    // same block
    for (const auto& it : grid) {
        int k = int(it.second.size());
        for (int i = 0; i < k; ++i) {
            for (int j = i+1; j < k; ++j) {
                candidate_closest(it.second[i], it.second[j]);
            }
        }
    }

    // adjacent blocks
    for (const auto& it : grid) {
        auto coord = it.first;
        for (int dx = 0; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 and dy == 0) continue;
                pt neighbour = pt(
                    coord.x  + dx, 
                    coord.y + dy
                );
                for (int i : it.second) {
                    if (not grid.count(neighbour)) continue;
                    for (int j : grid.at(neighbour)) {
                        candidate_closest(i, j);
                    }
                }
            }
        }
    }

    return closest;
}
int main(){
    HONDA
    int t;
    cin >> t;
    while (t--) {
        ll n;cin>>n;
        vector<pair<ll,ll>> points(n);
        vector<pair<ll,ll>> points2(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
            points2[i] = points[i];
            points[i].first = 4*points[i].first + 6*points[i].second;
            points[i].second = roundf(sqrt(3.0)*points[i].second);
        }
        vector<pt> P(n);
        for (int i = 0; i < n; ++i) {
            P[i] = pt(points[i].first, points[i].second);
        }
        auto ans = closest_pair_of_points(P);
        cout << 4*(points2[ans.first].first-points2[ans.second].first)*(points2[ans.first].first-points2[ans.second].first) + 
        12*(points2[ans.first].second-points2[ans.second].second)*(points2[ans.first].first-points2[ans.second].first) +
        12*(points2[ans.first].second-points2[ans.second].second)*(points2[ans.first].second-points2[ans.second].second)<<endl;
    }
    return 0;
}