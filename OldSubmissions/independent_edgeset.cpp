#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                                 
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           

void dfs(int node, vector<vector<int> > &graph, vector<bool> &vis, vector<int>&par){
    vis[node] = true;
    for(int neigh: graph[node]){
        if(!vis[neigh]){
            par[neigh] = node;
            dfs(neigh, graph, vis , par);
        }
    }
}

vector<vector<int> > DP(2e5+1,vector<int>(2,-1));

int f(int v, int k, vector<vector<int> > &graph, int n){
    if(DP[v][k] != -1){
        return DP[v][k];
    } else if(k == 0){
        int total = 0;
        for(int c: graph[v]){
            total += max(f(c,1,graph,n),f(c,0,graph,n));
        }
        DP[v][k] = total;
        return total;
    } else {
        int rt = 0;
        for(int c: graph[v]){
            rt = max(f(c,0, graph, n) + 1 + f(v,0,graph,n) - max(f(c,0,graph,n),f(c,1,graph,n)),rt);
        }
        DP[v][k] = rt;
        return rt;
    }
}
int main(){                                                                     
    ios::sync_with_stdio(false);                                                
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int> > graph(n);
    int a, b;
    for(int i = 0; i < n - 1; i++){
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> par(n,0);
    par[0] = -1;
    vector<bool> vis(n,false);
    dfs(0, graph, vis, par);
    for(int i = 0; i < n; i++){
        graph[i].clear();
    }
    for(int i = 1; i < n; i++){
        graph[par[i]].push_back(i);
    }
    cout << max(f(0,0,graph,n), f(0,1,graph,n)) << nl;
}    