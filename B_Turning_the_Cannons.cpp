#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<char> state(n+1, 0); // 0 = sleeping, 1 = ready
    vector<int> presses;

    for (int j = 1; j <= n; j++){
        if (!state[j]){
            int p = min(n, j + k);           // forced choice
            presses.push_back(p);
            int lo = max(1, p - k), hi = min(n, p + k);
            for (int x = lo; x <= hi; x++)
                state[x] ^= 1;
        }
    }

    cout << presses.size() << "\n";
    for (int i = 0; i < (int)presses.size(); i++)
        cout << presses[i] << " \n"[i+1==(int)presses.size()];
}