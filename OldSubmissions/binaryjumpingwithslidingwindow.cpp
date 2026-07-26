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
        dfs(neigh, depth, par, graph);
    }
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
        graph[e].push_back(i);
        e--;
        par[i] = e;
    }

    vector<int> depth(n,0);
    dfs(0, depth, graph);     
    
                                               
                                                                
                                                                                
}    