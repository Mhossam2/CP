#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fast ios::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    fast;

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int, ll>> A, B;
        A.reserve(n);
        B.reserve(n);

        vector<ll> a(n), b(n);
        for (auto &x : a) cin >> x;
        for (auto &x : b) cin >> x;

        for (int i = 0; i < n; i++) {
            A.push_back({i % m, a[i]});
            B.push_back({i % m, b[i]});
        }

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        cout << (A == B ? "YES\n" : "NO\n");
    }

    return 0;
}