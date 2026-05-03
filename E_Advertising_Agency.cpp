#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1e9 + 7;
const int MAXN = 1005;

ll fact[MAXN], invFact[MAXN];

// Fast exponentiation
ll modExp(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void init() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAXN - 1] = modExp(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

ll nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int &x : a) cin >> x;

        sort(a.begin(), a.end(), greater<int>());

        int x = a[k - 1];

        int total_x = count(a.begin(), a.end(), x);
        int need_x = count(a.begin(), a.begin() + k, x);

        cout << nCr(total_x, need_x) << "\n";
    }
}