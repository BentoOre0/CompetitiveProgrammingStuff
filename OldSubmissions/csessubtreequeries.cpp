#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';

ll timer;
vector<ll> tt, l, r, idx, tree;
vector<bool> vis;
vector<ll> vals;
vector<vector<int> > graph;
void euler(int v){
    vis[v] = true;
    idx[v] = timer;
    tt[timer] = v;
    l[v] = timer++;
    for(int neigh: graph[v]){
        if(!vis[neigh]){
            euler(neigh);
        }
    }
    r[v] = timer - 1;
}

class FenwickTree {
    private:
        vector<ll> tree;
        int sz;
    public:
        FenwickTree(vector<ll> nums){
            sz = nums.size();
            tree.assign(2*sz,0);
            for(int i = 0; i < nums.size(); i++){
                tree[i + 1] = nums[i]; 
            }

            for(int i = 1; i <= sz; i++){
                if(i + (i & -i) > sz){
                    continue;
                }
                tree[i + (i & -i)] += tree[i];
            }
        }

        ll PQ(int u){
            ll total = 0;
            while(u){
                total += tree[u];
                u -= u & -u;
            }
            return total;
        }
        ll RQ(int i, int j){
            return PQ(j) - PQ(i - 1);
        }

        void PU(int i, int k){
            while(i <= sz){
                tree[i] += k;
                i += i & -i;
            }
        }
};int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    timer = 0;
    int n, q;
    cin >> n >> q;

    tt.resize(n);
    vis.resize(n,false);
    l.resize(n);
    r.resize(n);
    idx.resize(n);
    vals.resize(n);
    graph.resize(n);
    for(int i = 0; i < n; i++){
        cin >> vals[i];
    }
    int u,v;
    for(int i = 0; i < n - 1; i++){
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    euler(0);
    
    vector<ll> tree(n);
    for(int i = 0; i < n; i++){
        tree[idx[i]] = vals[i];
    }
    FenwickTree FLATTENED(tree);

    int s, x;
    for(int i = 0; i < q; i++){
        int quer;
        cin >> quer;
        if(quer == 2){
            cin >> s;
            s--;
            cout << FLATTENED.RQ(l[s] + 1, r[s] + 1) << nl;
        } else {
            cin >> s >> x;
            s--;
            ll delta = x - vals[s];
            vals[s] = x;
            FLATTENED.PU(idx[s] + 1, delta);
        }
    }
    return 0;
}