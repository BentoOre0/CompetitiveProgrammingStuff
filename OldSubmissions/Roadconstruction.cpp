#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';


struct UnionFind{
    private:
        int nodes;
        vector<int> hts;
        vector<int> ids;
        vector<int> sizes;
        int max_size;
        int ccs;
    public:
        UnionFind(int n){
            max_size = 1;
            nodes = n;
            ccs = n;
            hts.resize(n,0);
            ids.resize(n,0);
            sizes.resize(n,0);
            for(int i = 0; i < nodes; i++){
                hts[i] = 0;
                ids[i] = i;
                sizes[i] = 1;
            }
        }

        int find(int n){
            int parent = ids[n];
            while(ids[parent] != parent){
                ids[parent] = ids[ids[parent]];
                parent = ids[parent];
            }
            return parent;
        }

        void unify(int a, int b){
            int anses_a = find(a), anses_b = find(b);
            if(anses_a == anses_b){
                return;
            } else {
                int ht_anses_a = hts[anses_a];
                int ht_anses_b = hts[anses_b];
                if(ht_anses_a > ht_anses_b){
                    ids[anses_b] = anses_a;
                    sizes[anses_a] += sizes[anses_b];
                } else if(ht_anses_b > ht_anses_a){
                    ids[anses_a] = anses_b;
                    sizes[anses_b] += sizes[anses_a];
                } else {
                    ids[anses_a] = anses_b;
                    hts[anses_b]++;
                    sizes[anses_b] += sizes[anses_a];
                }
                ccs--;
            }
            max_size = max(max_size,max(sizes[anses_a], sizes[anses_b]));
        }

        ll max_query(){
            return max_size;
        }
        
        ll cc_query(){
            return ccs;
        }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N,M;
    cin >> N >> M;
    UnionFind UF = UnionFind(N);
    for(int i = 0; i < M; i++){
        int u,v;
        cin >> u >> v;
        u--;
        v--;
        UF.unify(u,v);
        cout << UF.cc_query() << sp << UF.max_query() << nl;
    }

    
}
