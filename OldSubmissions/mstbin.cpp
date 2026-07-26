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
        ll sz;
        vector<ll> id;
        vector<ll> ht;
    public:
        UnionFind(ll n){
            sz = n;
            id.resize(n);
            ht.resize(n);
            for(ll i = 0; i < n; i++){
                id[i] = i;
                ht[i] = 0;
            }
        }


        ll find(ll i){
            ll prt = i;
            while(id[prt] != prt){
                id[prt] = id[id[prt]];
                prt = id[prt];
            }
            return prt;
        }


        void unify(ll i, ll j){
            ll pi = find(i), pj = find(j);
            if(pi == pj){
                return;
            } else {
                if(ht[pi] == ht[pj]){
                    id[pi] = pj;
                    ht[pj]++;
                } else if(ht[pi] > ht[pj]){
                    id[pj] = pi;
                } else if(ht[pj] > ht[pi]){
                    id[pi] = pj;
                }
                return;
            }
        }
};




ll ansesquery(ll node, ll k, vector<vector<ll>> &anses) {
    ll v = node;
    while(k){
        ll LS = k & -k;
        v = anses[v][__builtin_ctz(LS)];
        k -= LS;
    }
    return v;
}
ll maxansesquery(ll node, ll k, vector<vector<ll> > &maxanses, vector<vector<ll> > &anses){
    ll v = node;
    ll LS;
    ll rt = 0;
    while(k){
        LS = k&-k;
        rt = max(rt,maxanses[v][__builtin_ctz(LS)]);
        v = anses[v][__builtin_ctz(LS)];
        k -= LS;
    }
    return rt;
}
int main(){                                                                    
    ios::sync_with_stdio(false);                                                
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    vector<tuple<ll,ll,ll> > E;
    vector<tuple<ll,ll,ll> > copyE;
    vector<vector<pii> > graph(n);
    ll u,v,w;
    for(ll i = 0; i < m; i++){
        cin >> u >> v >> w;
        u--; v--;
       
        E.push_back({u,v,w});
        copyE.push_back({u,v,w});
    }
   
    UnionFind UF = UnionFind(n);
    sort(E.begin(), E.end(), [&](const auto &a, const auto &b){
        return get<2>(a) < get<2>(b);
    });
    ll MST = 0;
    set<tuple<ll,ll,ll> > Elist;
    for(auto &[u,v,w] : E){
        if(UF.find(u) != UF.find(v)){
            UF.unify(u,v);
            MST += w;
            Elist.insert({u,v,w});
        }
    }


    for(auto &[u,v,w]: Elist){
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
        // cout << u + 1 << sp << v + 1 << sp << w << nl;
        // cout << nl;
    }


    //GRAPH IS NOW OF MST
    vector<pll> par(n, {-1,0});
    vector<ll> depth(n,0);
    vector<bool> vis(n, false);
    queue<ll> q;
    q.push(0);
    while(!q.empty()){
        ll node = q.front(); q.pop();
        vis[node] = true;
        for(auto &[neigh, w]: graph[node]){
            if(!vis[neigh]){
                par[neigh] = {node,w};
                depth[neigh] = depth[node] + 1;
                q.push(neigh);
            }
        }
    }
    vector<vector<ll> > anses(n, vector<ll>(18,-1));
    vector<vector<ll> > mxedge(n, vector<ll>(18,0));
    for(ll i = 0; i < n; i++){
        anses[i][0] = par[i].first;
        mxedge[i][0] = par[i].second;
        // cout << i + 1 << sp << anses[i][0] + 1 << sp << mxedge[i][0] << nl;
    }
    for(ll k = 0; k < 17; k++){
        for(ll node = 0; node < n; node++){
            if(anses[node][k] == -1){
                anses[node][k + 1] = -1;
                mxedge[node][k+1] = mxedge[node][k];
            } else {
                anses[node][k+1] = anses[anses[node][k]][k];
                mxedge[node][k+1] = max(mxedge[node][k], mxedge[anses[node][k]][k]);  
            }
        }
    }



    for(auto &[a,b,w] : copyE){
        if(Elist.count({u,v,w})){
            cout << MST << nl;
        } else {
            // cout << u << sp << v << sp << w << nl;
            ll u = a;
            ll v = b;
            ll LCA;
            ll depthdiff;
            if (depth[u] < depth[v]) {
                depthdiff = depth[v] - depth[u];
                v = ansesquery(v, depthdiff, anses);
            } else if (depth[v] < depth[u]) {
                depthdiff = depth[u] - depth[v];
                u = ansesquery(u, depthdiff, anses);
            }
            if(u == v){
                LCA = u;
            } else {
                for(ll k = 17; k >= 0; k--){
                    if(anses[u][k] != anses[v][k]){
                        u = anses[u][k];
                        v = anses[v][k];
                    }
                }
                LCA = anses[u][0];
            }


            cout << MST - max(maxansesquery(a,depth[a] - depth[LCA],mxedge, anses),maxansesquery(b,depth[b] - depth[LCA],mxedge, anses)) + w << nl;
        }
    }
}    