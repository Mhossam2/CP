#include <bits/stdc++.h>
using namespace std;

int main(){
    int N,Q;
    scanf("%d %d",&N,&Q);
    vector<long long> A(N);
    long long mx=0;
    for(int i=0;i<N;i++){ scanf("%lld",&A[i]); mx=max(mx,A[i]); }

    vector<int> P(Q),R(Q);
    for(int i=0;i<Q;i++) scanf("%d %d",&P[i],&R[i]);

    // value -> sorted indices
    unordered_map<long long, vector<int>> pos;
    pos.reserve(N*2);
    for(int i=0;i<N;i++) pos[A[i]].push_back(i);

    // generate Fibonacci numbers (1,2,3,5,8,...) up to 2*mx
    vector<long long> fibs;
    long long a=1,b=2;
    fibs.push_back(a);
    fibs.push_back(b);
    long long limit = 2*mx;
    while(true){
        long long c=a+b;
        if(c>limit) break;
        fibs.push_back(c);
        a=b; b=c;
    }

    vector<int> ans(Q,0);
    const int INF = INT32_MAX;
    vector<int> bestJ(N), sufmin(N+1);

    for(long long F: fibs){
        for(int i=0;i<N;i++){
            long long target = F - A[i];
            bestJ[i]=INF;
            auto it = pos.find(target);
            if(it!=pos.end()){
                auto &v = it->second;
                int lo=0, hi=(int)v.size();
                while(lo<hi){
                    int mid=(lo+hi)/2;
                    if(v[mid]>i) hi=mid; else lo=mid+1;
                }
                if(lo<(int)v.size()) bestJ[i]=v[lo];
            }
        }
        sufmin[N]=INF;
        for(int i=N-1;i>=0;i--) sufmin[i]=min(bestJ[i], sufmin[i+1]);

        for(int q=0;q<Q;q++)
            if(sufmin[P[q]] <= R[q]) ans[q]++;
    }

    for(int q=0;q<Q;q++) printf("%d\n", ans[q]);
    return 0;
}