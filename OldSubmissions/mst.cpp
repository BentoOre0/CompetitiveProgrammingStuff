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
        vector<int> id, ht;
    public:
        UnionFind(int n){
            sz = n;
            id.resize(sz);
            ht.resize(sz);
            for(int i = 0; i < sz; i++){
                id[i] = i;
                ht[i] = 0;
            }
        }
    int find(int u){
        int prnt = id[u];
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
                id[r_v] = r_u;
                ht[r_u]++;
            }
        }
    }
};


int main(){
    ll V,E;
    cin >> V >> E;
    if(V == 1){
        while(true){
            cout << '.' << nl;
        }
    }
    vector<tuple<ll,ll,ll> > edgelist;
    ll u,v,w;
    for(int i = 0; i < E; i++){
        cin >> u >> v >> w;
        u--;
        v--;
        edgelist.push_back({u,v,w});
    }

    sort(edgelist.begin(), edgelist.end(),[&](const auto &a, const auto &b){
        return get<2>(a) < get<2>(b);
    });
    ll count = 0;
    ll answer = 0;
    UnionFind UF = UnionFind(V);
    vector<bool> vis(V,false);
    for(auto &[u,v,w]: edgelist){
        if(UF.find(u) != UF.find(v)){
            count++;
            answer += w;
            UF.unify(u,v);
            vis[u] = true;
            vis[v] = true;
        }
    }
    if(count == V - 1){
        cout << answer << nl;
    } else {
        cout << "IMPOSSIBLE" << nl;
    }
}