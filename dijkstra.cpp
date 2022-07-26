//codeforces 20C

#include<bits/stdc++.h>
using namespace std;
#define faster_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define sz 100005
typedef long long ll;
ll const infinity = 1e18;
 
vector<pair<ll,ll> > graph[sz];
multimap<ll,ll> q;
multimap<ll,ll> :: iterator it;
ll parent[sz],Distance[sz];
bool visit[sz];
 
void print_path(int source,int n)
{
    if(n==source) return;
    if(parent[n] == -1){
        cout<<-1<<endl;
        exit(0);
    }
    print_path(source,parent[n]);
    cout<<parent[n]<<" ";
}
 
void initialize(int source)
{
    for(int i=1;i<=sz;i++){
        Distance[i] = infinity;
        parent[i] = -1;
    }
 
    Distance[source] = 0;
    parent[source] = source;
    q.insert(make_pair(0,source));
}
 
 
void Dijkstra(int source)
{
    initialize(source);
 
    while(!q.empty()){
        it = q.begin();
        int u = it->second;
        q.erase(it);
        if(!visit[u]){
            for(int i=0;i<graph[u].size();i++){
                int v = graph[u][i].first;
                if(Distance[u]+graph[u][i].second < Distance[v]){
                    Distance[v] = Distance[u]+graph[u][i].second;
                    q.insert(make_pair(Distance[v],v));
                    parent[v] = u;
                }
            }
        }
        visit[u] = true;
    }
}
 
int main()
{
    faster_io;
    int vertex,edge,x,y,c,source;
    cin>>vertex>>edge;
 
    for(int i=0;i<edge;i++){
        cin>>x>>y>>c;
        graph[x].push_back(make_pair(y,c));
        graph[y].push_back(make_pair(x,c));
    }
 
    Dijkstra(1);
    print_path(1,vertex);
    cout<<vertex<<endl;
 
    return 0;
}

// 5 6
// 1 2 2
// 2 5 5
// 2 3 4
// 1 4 1
// 4 3 3
// 3 5 1

//       if (!visit[u]) {
//             for (auto it : v[u]) {
//                 ll vv = it.F;
//                 ll c =  it.S;
//                 if (dist[vv] > max(dist[u], c)) {              // taking the max of any paths as cost 
//                     dist[vv] = max(dist[u], c);                // instead of sum of the weights
//                     q.insert({c, vv});
//                 }
//             }
//         }


