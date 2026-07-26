#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

vector<int> ts;
void topsort(int u, vector<bool> &vis, vector<vector<int> > &graph){
    vis[u] = true;
    for(int v: graph[u]){
        if(!vis[v]){
            topsort(v,vis,graph);
        }
    }
    ts.push_back(u);
}
int main() {
    int T;
    cin >> T;
    cin.ignore();

    for(int i = 0; i <= T; i++){
        string line;
        unordered_map<char,int> translate;
        unordered_map<int,char> backtranslate;
        unordered_map<int,int> w;
        vector<vector<int> > graph;
        vector<pii> edgelist;
        vector<int> src;  
        int V = 0;

        while(getline(cin, line) && !line.empty()) {
            istringstream iss(line);
            string node;
            int weight;
            string edges = "";
             
            iss >> node >> weight;
            if (!(iss >> edges)) {
                edges = "";  // if no edges, set to empty string
            }
            char nod1 = node[0];
            vector<char> temp;
            if(!translate.count(nod1)){
                translate[nod1] = V;
                backtranslate[V] = nod1;
                V++;
            }
            if(edges.size() == 0){
                src.push_back(translate[nod1]);
            }
            for(char c: edges){
                temp.push_back(c);
                if(!translate.count(c)){
                    translate[c] = V;
                    backtranslate[V] = c;
                    V++;
                }
                edgelist.push_back({translate[c],translate[nod1]});
            }
            w[translate[nod1]] = weight;
        }
        if(i == 0){
            continue;
        }
        graph.resize(V);
        for(auto &[u,v] : edgelist){
            graph[u].push_back(v);
        }
        vector<bool> vis(V,false);
        ts.clear();
        for(int i = 0; i < V; i++){
            if(!vis[i]){
                topsort(i, vis, graph);
            }
        }
        reverse(ts.begin(),ts.end());
        vector<int> distance(V,0);
        for(int u: src){
            distance[u] = w[u];
        }
        
        for(int u : ts){
            for(int v: graph[u]){
                distance[v] = max(distance[u] + w[v], distance[v]);
            }
        }
        int worstcase = distance[ts[0]];
        for(int i = 0; i < V; i++){
            worstcase = max(worstcase,distance[i]);
        }
        cout << worstcase << nl;
        if(i != T){
            cout << nl;
        }
        

    }

    return 0;
}