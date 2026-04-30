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

const long long INF = 1e18;

struct Edge {
    int to, cap, flow, cost, rev;
};

vector<Edge> adj[210];
long long dist_node[210];
int p_node[210], p_edge[210];

void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
    adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
}

bool spfa(int s, int t, int &flow, long long &cost, int K) {
    fill(dist_node, dist_node + 210, INF);
    vector<bool> in_q(210, false);
    queue<int> q;
    dist_node[s] = 0; q.push(s); in_q[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop(); in_q[u] = false;
        for (int i = 0; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            if (e.cap > e.flow && dist_node[e.to] > dist_node[u] + e.cost) {
                dist_node[e.to] = dist_node[u] + e.cost;
                p_node[e.to] = u; p_edge[e.to] = i;
                if (!in_q[e.to]) { q.push(e.to); in_q[e.to] = true; }
            }
        }
    }
    if (dist_node[t] == INF) return false;
    int push = min(K - flow, 1);
    flow += push;
    cost += (long long)push * dist_node[t];
    for (int v = t; v != s; v = p_node[v]) {
        adj[p_node[v]][p_edge[v]].flow += push;
        adj[v][adj[p_node[v]][p_edge[v]].rev].flow -= push;
    }
    return true;
}

int main() {
    int N, P, Q, K;
    cin >> N >> P >> Q >> K;
    string S; cin >> S;
    vector<pair<int, int>> A(P), B(Q);
    for (int i = 0; i < P; ++i) cin >> A[i].first >> A[i].second;
    for (int i = 0; i < Q; ++i) cin >> B[i].first >> B[i].second;

    int src = 0, sink = P + Q + 1;
    for (int i = 0; i < P; ++i) {
        add_edge(src, i + 1, 1, 0);
        for (int j = 0; j < Q; ++j) {
            int lenA = A[i].second - A[i].first + 1;
            int lenB = B[j].second - B[j].first + 1;
            int common = 0;
            int p1 = A[i].second - 1, p2 = B[j].second - 1;
            while (common < lenA && common < lenB && S[p1] == S[p2]) {
                common++; p1--; p2--;
            }
            add_edge(i + 1, P + j + 1, 1, lenA + lenB - 2 * common);
        }
    }
    for (int j = 0; j < Q; ++j) add_edge(P + j + 1, sink, 1, 0);

    int flow = 0; long long min_cost = 0;
    while (flow < K && spfa(src, sink, flow, min_cost, K));
    cout << min_cost << endl;
    return 0;
}