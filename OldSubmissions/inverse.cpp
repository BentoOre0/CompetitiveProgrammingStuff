#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

class UnionFind{
    private:
        int sz;
        vector<int> ht;
        vector<int> id;
    public:
        UnionFind(int n){
            sz = n;
            ht.resize(sz);
            id.resize(sz);
            for(int i = 0; i < sz; i++){
                ht[i] = 0;
                id[i] = i;
            }
        }
    int find(int i){
        int prnt = id[i];
        while(id[prnt] != prnt){
            id[prnt] = id[id[prnt]];
            prnt = id[prnt];
        }
        return prnt;
    }

    void unify(int u, int v){
        int r_u = find(u), r_v = find(v);
        if(r_u == r_v){
            return;
        } else {
            if(ht[r_u] > ht[r_v]){
                id[r_v] = r_u;
            } else if(ht[r_v] > ht[r_u]){
                id[r_u] = r_v;
            } else {
                id[r_u] = r_v;
                ht[r_v]++;
            }
        }
    }
};

bool comp(vector<vector<ll> > &dist, int N){
    for(int i = 0; i < N; i++){
        if(dist[i][i] != 0){
            return false;
        }
        for(int j = 0; j < N; j++){
            if(dist[i][j] != dist[j][i]){
                return false;
            }
        }
    }
    return true;
}

// bool check_path_is(int u, int v, int w, vector<vector<pll> >&adj, int N){
//     vector<ll> d(N, INF);
//     queue<ll> Q;
//     Q.push(u);
//     d[u] = 0;
//     while(!Q.empty()){
//         ll node = Q.front(); Q.pop();
//         for(auto &[neigh,w] : adj[node]){
//             if(d[neigh] == INF){
//                 d[neigh] = d[node] + w;
//                 Q.push(neigh);
//             }
//         }
//         if(d[v] == w){
//             return true;
//         }
//     }
//     return false;
// }



bool connected(vector<vector<pll> > &adj, int N){
    vector<bool> vis(N,false);
    queue<ll> Q;
    Q.push(0);
    while(!Q.empty()){
        ll node = Q.front(); Q.pop();
        vis[node] = true;
        for(auto &[neigh,w] : adj[node]){
            if(!vis[neigh]){
                Q.push(neigh);
            }
        }
    }
    for(int i = 0; i < N; i++){
        if(!vis[i]){
            return false;
        }
    }
    return true;
}

bool check_bfs(int i, vector<vector<pll> > &adj, vector<vector<ll> > &dist){
    vector<ll> d(adj.size(),INF);
    d[i] = 0;
    queue<ll> Q;
    Q.push(i);
    while(!Q.empty()){
        int node = Q.front(); Q.pop();
        for(auto &[neigh,w] : adj[node]){
            if(d[neigh] == INF){
                Q.push(neigh);
                d[neigh] = d[node] + w;
            }
        }
    }
    for(int j = 0; j < adj.size(); j++){
        if(d[j] != dist[i][j]){
            // cout << j << sp << d[j] << sp << dist[i][j] << nl;
            return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<ll> > dist(N, vector<ll>(N,0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> dist[i][j];
        }
    }
    bool flag1 = comp(dist, N);
    if(flag1){
        vector<tuple<ll,ll,ll> > edgelist;
        edgelist.reserve(N*N);
        for(int i = 0; i < N; i++){
            for(int j = i + 1; j < N; j++){
                if(dist[i][j] != 0){
                    edgelist.push_back({i,j, dist[i][j]});
                }
            }
        }
        sort(edgelist.begin(), edgelist.end(),[&](const auto &a, const auto &b){
            return get<2>(a) < get<2>(b);
        });
        UnionFind UF = UnionFind(N);
        vector<vector<pll> > adj(N);
        for(int i = 0; i < edgelist.size(); i++){
            auto &[u,v,w] = edgelist[i];
            if(UF.find(u) != UF.find(v)){
                UF.unify(u,v);
                adj[u].push_back({v,w});
                adj[v].push_back({u,w});
            }
        }
        bool flag2 = connected(adj, N);
        bool flag3 = true;
        for(int i = 0; i < N; i++){
            flag3 = flag3 & check_bfs(i,adj, dist);
        } 
        if(flag2 && flag3){
            cout << "YES" << nl;
        } else {
            cout << "NO" << nl;
        }
    } else {
        cout << "NO" << nl;
    }
}