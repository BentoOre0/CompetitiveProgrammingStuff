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
            int ri = query(i);
            int rj = query(j);
            if(ri == rj){
                return;
            } else {
                if(ht[ri] > ht[rj]){
                    prnt[rj] = ri;
                } else if(ht[rj] > ht[ri]){
                    prnt[ri] = rj;
                } else {
                    prnt[rj] = ri;
                    ht[ri]++;
                }
            }
        }
};

int main(){
    int n;
    int d;
    ll count = 0;
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
        edgelist.push_back({u,v});
    }
    UnionFind UF = UnionFind(n);
    for(auto [u,v]: edgelist){
        UF.unify(u,v);
    }

    set<int> temp;
    for(int i = 0; i < n; i++){
        temp.insert(UF.query(i));
    }
    int ds = temp.size();
    for(int aa = 0; aa <= d; aa++){
        if(aa != 0){
            cin >> u >> v;
            u--; v--;
            if(UF.query(u) != UF.query(v)){
                ds--;
            }
            edgelist.push_back({u,v});
            UF.unify(u,v);
        }
        cout << ds - 1 << nl;
    }
}