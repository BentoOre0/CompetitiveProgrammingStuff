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

    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    int N, Q;
    cin >> N >> Q;
    vector<vector<pll> > adj(N);
    for(int i = 0; i < N - 1; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    queue<ll> q;
    vector<bool> vis;
    for(int a = 0; a < Q; a++){
        ll k, src;
        cin >> k >> src;
        src--;
        q.push(src);
        vis.clear();
        vis.resize(N, false);
        while(!q.empty()){
            ll node = q.front(); q.pop();
            if(vis[node]){
                continue;
            }
            vis[node] = true;
            for(auto &[neigh, weight] : adj[node]){
                if(weight >= k){
                    q.push(neigh);
                }
            }
        }
        int count = 0;
        for(int i = 0 ; i < N; i++){
            if(vis[i]){
                count++;
            }
        }
        cout << count - 1 << nl;
    }
    
    return 0;
}
