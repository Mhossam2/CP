#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
#define elsady ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define test int t;cin>>t;while(t--)
#define fs first
#define sc second
#define ll long long
#define endl '\n'
#define en end()
#define be begin()
#define no cout<<"NO"<<endl
#define yes cout<<"YES"<<endl
#define all(v) v.be,v.en
#define gr greater<int>
#define pii pair<int,int>
#define tup tuple<int,int,int>
template <typename T> // T -> (can be integer, float or pair of int etc.)
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N=1e6,N2=2e5+3;
int spf[N+1];
void pre()
{
    for(int i=0;i<=N;i++)spf[i]=i;
    for(int i=2;i<=N;i++)
    {
        if(spf[i]==i)
        {
            for(int j=2*i;j<=N;j+=i)
            {
                if(spf[j]==j)
                  spf[j]=i;
            }
        }
    }
}

vector<int> pr(int x)
{
   vector<int>c;
    while(x>1)
    {
        c.push_back(spf[x]);
        int w=spf[x];
        while(spf[x]==w)
          x/=spf[x];
    }

    return c;
}

int s,e,n;
vector<int>a(N);
vector<set<int>>st(N);
vector<vector<int>>p(N2);
vector<vector<pii>>adj;

ll dijkstra() 
{
    vector<ll>dis(n+1+N+1,-1);
    dis[s]=0;

    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;
    q.push({0,s});

    while (!q.empty()) 
    {
        int v=q.top().second;
        int d_v=q.top().first;
        q.pop();
        if (d_v!=dis[v])
            continue;

        if(v==e)
          return dis[v];

        for(auto [u,w]:adj[v])
        {
            if(dis[u]==-1||dis[v]+w<dis[u])
            {
                q.push({dis[v]+w,u});
                dis[u]=dis[v]+w;
            }
        }
    }

    return dis[e];
}

void solve()
{  
    cin>>n>>s>>e;
    s--;
    e--;

    map<int,int>mp;
    adj.assign(n+1+N+1,{});
    int c=0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        p[i]=pr(a[i]);
        for(int pr:p[i])
        {
            if(!mp.count(pr))
                mp[pr]=n+1+(c++);
            int w=mp[pr];
            adj[w].push_back({i,a[i]});
            adj[i].push_back({w,a[i]});
        }
    }    

    if(__gcd(a[s],a[e])>1)
      return void(cout<<(s==e?0:a[s]+a[e]));
    cout<<dijkstra();
}

signed main()
{
    elsady
    pre();
    solve();
}