#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

void dfs(int N, vector<bool> &vis,vector<vector<ll> > &adj, vector<ll> &topsort){
    if(!vis[N]){
        vis[N] = true;
        for(int neigh: adj[N]){
            if(!vis[neigh]){
                dfs(neigh, vis,adj,topsort);
            }
        }
        topsort.push_back(N);
    }
}

int k_th_ancestor(int k, int N, vector<vector<ll> > &anses){
    int node = N;
    while(k){
        int ls = k & -k;
        node = anses[__builtin_ctz(ls)][node];
        k -= ls;
    }
    return node;
}

void fill_distances(int node, vector<ll> &dist, vector<vector<ll> > &adj){
    for(int neigh: adj[node]){
        if(neigh != 0 && (dist[neigh] == 0)){
            dist[neigh] = dist[node]+1;
            fill_distances(neigh,dist,adj);
        }
    }
}

int LCA(int u, int v, vector<ll> &dist, vector<vector<ll> > &anses){
    if(dist[u] > dist[v]){
        swap(u,v);
    }
    // u is always <= dist[v]
    int K = dist[v] - dist[u];
    v = k_th_ancestor(K,v,anses);
    if(u == v){
        return v;
    } else {
        for(int k = 17; k >= 0; k--){
            if(anses[k][u] != anses[k][v]){
                u = anses[k][u];
                v = anses[k][v];
            }
        }
        return anses[0][u];
    }
    
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<vector<ll> > anses(18,vector<ll>(N,0));
    vector<vector<ll> > adj(N);
    int u,v;
    for(int i = 0; i < N - 1; i++){
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> vis(N,false);
    vector<ll> RPSO;
    //root tree
    dfs(0,vis,adj, RPSO);
    reverse(RPSO.begin(),RPSO.end());
    vector<pll> rootededgelist;
    for(int i = 0; i < N; i++){
        vis[i] = false;
    }
    for(int num: RPSO){
        vis[num] = true;
        for(int neigh: adj[num]){
            if(!vis[neigh]){
                rootededgelist.push_back({num,neigh});
                
            }
        }
    }
    
    vector<ll> parent(N,-1);
    for(auto &[p, c]: rootededgelist){
        parent[c] = p;
    }
    parent[0] = 0;
    for(int i = 0; i < N; i++){
        anses[0][i] = parent[i];
    }
    for(int k = 1; k <= 17; k++){
        for(int node = 0; node < N; node++){
            anses[k][node] = anses[k-1][anses[k-1][node]];
        }
    }
    vector<ll> distances(N,0);
    fill_distances(0,distances,adj);
    int a, b;
    for(int q = 0; q < Q; q++){
        cin >> a >> b;
        a--;
        b--;
        cout << distances[a] + distances[b] - 2*distances[LCA(a,b, distances,anses)] << nl; 
    }
}
