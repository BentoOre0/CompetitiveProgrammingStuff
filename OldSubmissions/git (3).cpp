#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';


class UnionFind{
    private:
        int sz;
        vector<int> prnt;
        vector<int> ht;
    public:
        UnionFind(int n){
            sz = n;
            prnt.resize(n);
            ht.resize(n,0);
            for(int i = 0; i < sz; i++){
                prnt[i] = i;
            }
        }

        int query(int i){
            int node = i;
            while(prnt[node] != node){
                prnt[node] = prnt[prnt[node]];
                node = prnt[node];
            }
            return node;
        }

        void unify(int i, int j){
            if(query(i) == query(j)){
                return;
            } else {
                if(ht[i] > ht[j]){
                    prnt[j] = i;
                } else if(ht[j] > ht[i]){
                    prnt[i] = j;
                } else {
                    prnt[i] = j;
                    ht[i]++;
                }
            }
        }

};

int main(){
    int n;
    int d;
    cin >> n;
    cin >> d;
    vector<int> costs;
    int num;
    for(int i = 0; i < n; i++){
        cin >> num;
        if(num != 1){
            return 0;
        }
        costs.push_back(num);
    }
    map<int,map<int,int> > adj;
    int u, v;
    vector<pii> edgelist;
    for(int i = 0; i < n - 1; i++){
        cin >> u >> v;
        u--; v--;
        if(adj[u].count(v)){
            adj[u][v]++;
        } else {
            adj[u][v] = 1;
        }
        if(adj[v].count(u)){
            adj[v][u]++;
        } else {
            adj[v][u] = 1;
        }
    }
    int count = 0;
    for(int aa = 0; aa <= d; aa++){
        vector<bool> vis(n, false);   
        if(aa != 0){
            cin >> u >> v;
            u--; v--;
            if(adj[u].count(v)){
                adj[u][v]++;
            } else {
                adj[u][v] = 1;
            }
            if(adj[v].count(u)){
                adj[v][u]++;
            } else {
                adj[v][u] = 1;
            }
            if(!vis[v] || !vis[u]){
                count--;
            }
        }

        if(count == 0){
            for(int i = 0; i < n; i++){
                if(!vis[i]){
                    queue<int> q;
                    count++;
                    q.push(i);
                    while(!q.empty()){
                        
                        int node = q.front();
                        // cout << node << sp;
                        q.pop();
                        vis[node] = true;
                        for(int j = 0; j < n; j++){
                            if(adj[node].count(j)){
                                // cout << j << nl;
                                
                                if(!vis[j]){
                                    q.push(j);   
                                }
                            }
                            // return 0;
                        }
                    }
                    // cout << nl;
                }
            }
        }

        
        
        cout << count - 1 << nl;
    }
}