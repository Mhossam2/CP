#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N;
        scanf("%d", &N);
        long long L = 0;
        long long U = LLONG_MAX;
        long long offset = 0;
        for(int i=0;i<N;i++){
            long long m;
            char sign[3];
            scanf("%lld %s", &m, sign);
            if(sign[0]=='+'){
                long long need = m - offset;
                if(need > L) L = need;
                offset -= (m + 25);
            } else {
                long long lim = m - offset - 1;
                if(lim < U) U = lim;
            }
        }
        if(L < 0) L = 0;
        long long ans = U - L + 1;
        if(ans < 0) ans = 0;
        printf("%lld\n", ans);
    }
    return 0;
}