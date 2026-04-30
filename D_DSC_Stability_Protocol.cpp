#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll s;
    cin >> n >> s;

    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    multiset<ll> st;
    ll sum = 0;
    int l = 0;

    ll ans = 0;
    bool possible = true;

    for (int r = 0; r < n; r++) {
        st.insert(a[r]);
        sum += a[r];

        while (sum >= s) {
            if (st.size() < 2) {
                possible = false;
                break;
            }

            auto it = st.end();
            --it; 
            --it; 
            ans += *it;

            sum -= a[l];
            st.erase(st.find(a[l]));
            l++;
        }

        if (!possible) break;
    }

    if (!possible) cout << -1 << "\n";
    else cout << ans << "\n";
}