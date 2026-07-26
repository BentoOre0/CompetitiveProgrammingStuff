#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
#define FOR(L, R) for(int i = L; i < R; ++i)
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';
ll f(int mask, int n, int K,vector<vector<vector<int> > > &adj, vector<int> &color, vector<vector<ll> > &dp){
    if(dp[mask][n] != -1){
        return dp[mask][n];
    } else if(mask == 0){
        return 0;
    } else {
        ll count = 0;
        for(int cl = 0; cl < K; cl++){
            if((mask & (1 << cl)) != 0){
                for(int neigh: adj[n][cl]){
                    count += 1 + f(mask ^ (1 << color[neigh]), neigh, K, adj, color, dp);
                }
            }
        }
        dp[mask][n] = count;
        return count;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<vector<int> > > adj(N, vector<vector<int> >(K));
    vector<int> graph_color(N,0); 
    int col;
    for(int i = 0; i < N; i++){
        cin >> col;
        col--;
        graph_color[i] = col;
    }
    int u,v;
    for(int i = 0; i < M; i++){
        cin >> u >> v;
        u--; v--;
        if(graph_color[u] != graph_color[v]){
            adj[u][graph_color[v]].push_back(v);
            adj[v][graph_color[u]].push_back(u);
        }
    }
    vector<vector<ll> > dp((1 << K) - 1, vector<ll>(N, -1));
    int color_mask = (1 << K) - 1;
    ll ans = 0;
    for(int i = 0; i < N; i++){
        ans += f(color_mask ^ (1 << graph_color[i]), i, K, adj, graph_color, dp);
    }
    cout << ans << nl;
}