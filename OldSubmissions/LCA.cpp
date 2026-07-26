#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                                 
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           

void dfs(int node, vector<int> &depth, vector<vector<int> > &graph){
    for(int neigh: graph[node]){
        depth[neigh] = depth[node] + 1;
        dfs(neigh, depth, graph);
    }
}


int ansestorquery(int k, int node, vector<vector<int> > &anses){
    int v = node;
    int LS;
    while(k){
        LS = k & -k;
        v = anses[__builtin_ctz(LS)][v]; 
        k -= LS;
    }
    return v;
}
int main(){                                                                     
    ios::sync_with_stdio(false);                                                
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<vector<int> > graph(n);
    vector<int> par(n);
    par[0] = -1;
    int e;
    for(int i = 1; i < n; i++){
        cin >> e;
        e--;
        graph[e].push_back(i);
        par[i] = e;
    }

    vector<int> depth(n,0);
    dfs(0, depth, graph);

    vector<vector<int> > anses(18, vector<int>(n,0));

    for(int i = 0; i < n; i++){
        anses[0][i] = par[i];
    }

    for(int k = 0; k < 17; k++){
        for(int i = 0; i < n; i++){
            anses[k + 1][i] = anses[k][anses[k][i]];
        }
    }
    int u,v;
    for(int i = 0; i < q; i++){ 
        cin >> u >> v;
        u--; v--;
        int depthdiff;
        if(depth[u] < depth[v]){
            depthdiff= depth[v]-depth[u];
            v = ansestorquery(depthdiff,v,anses);
        }
        if(depth[v] < depth[u]){
            depthdiff= depth[u]-depth[v];
            u = ansestorquery(depthdiff,u,anses);
        }
        // cout << u << sp << v << nl;
        // cout << depth[u] << sp << depth[v] << nl;
        if(u == v){
            cout << u + 1 << nl;
        } else {
            for(int k = 17; k >= 0; k--){
                if(anses[k][v] != anses[k][u]){
                    u = anses[k][u];
                    v = anses[k][v];
                }
            }
            cout << anses[0][u] + 1 << nl;
        }
    }
    

}    