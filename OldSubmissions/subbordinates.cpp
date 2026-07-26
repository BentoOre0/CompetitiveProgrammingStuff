#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    if(N == 1){
        cout << 0 << nl;
        return 0;
    }
    vector<vector<int> > adj(N);
    for(int i = 0; i < N - 1; i++){
        int A, B;
        cin >> A >> B;
        A--; B--;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    vector<int> dist(N,400000);
    vector<bool> vis(N,false);
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        if(!vis[node]){
            vis[node] = true;
            for(int neigh: adj[node]){
                if(!vis[neigh]){
                    dist[neigh] = min(dist[node] + 1, dist[neigh]);
                    q.push(neigh);
                }
            }
        }
    }
    int mxdist = 0;
    int gnode = 0;
    for(int i = 0; i < N; i++){
        if(dist[i] > mxdist){
            gnode = i;
            mxdist = dist[i];
        }
    }
    dist.clear();
    vis.clear();
    dist.resize(N,400000);
    vis.resize(N,false);
    q.push(gnode);
    dist[gnode] = 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        if(!vis[node]){
            vis[node] = true;
            for(int neigh: adj[node]){
                if(!vis[neigh]){
                    dist[neigh] = min(dist[node] + 1, dist[neigh]);
                    q.push(neigh);
                }
            }
        }
    }
    int best_dist = 0;
    int leaf_node_start = -1;
    for(int i = 0; i < N; i++){
        if(dist[i] > best_dist){
            leaf_node_start = i;
            best_dist = dist[i];
        }
    }

    vector<int> dist_S(N,400000);
    q.push(leaf_node_start);
    dist_S[leaf_node_start] = 0;
    vector<bool> vis_S(N,false);
    while(!q.empty()){
        int node = q.front(); q.pop();
        if(vis_S[node]){
            continue;
        }
        vis_S[node] = true;
        for(int neigh: adj[node]){
            dist_S[neigh] = min(dist_S[node] + 1, dist_S[neigh]); 
            q.push(neigh);
        }
    }
    int leaf_node_end = -1;
    int max_dist = 0;

    for(int i = 0; i < N; i++){
        cout << max(dist_S[i], dist[i]) << sp;
    }
}
