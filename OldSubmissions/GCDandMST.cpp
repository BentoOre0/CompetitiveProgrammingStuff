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
        vector<int> ht;
        vector<int> id;
    public:
        UnionFind(int u){
            sz = u;
            ht.resize(sz);
            id.resize(sz);
            for(int i = 0; i < sz; i++){
                id[i] = i;
                ht[i] = 0;
            }
        }

    int find(int i){
        int prnt = id[i];
        while(id[prnt] != prnt){
            id[prnt] = id[id[prnt]];
            prnt = id[prnt];
        }
        return prnt;
    }

    void unify(int u, int v){
        int ru = find(u), rv = find(v);
        if(ru == rv){
            return;
        } else {
            if(ht[ru] > ht[rv]){
                id[rv] = ru;
            } else if(ht[rv] > ht[ru]){
                id[ru] = rv;
            } else {
                id[rv] = ru;
                ht[rv]++;
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        ll V, E;
        cin >> V >> E;
        vector<ll> arrs;
        ll nums;
        vector<pll> search;
        int count = V;
        for(int i = 0; i < V; i++){
            cin >> nums;
            arrs.push_back(nums);
            if(nums < E){
                search.push_back({nums,i});
            }
        }

        ll MST = 0;
        vector<bool> vis(V,false);
        sort(search.begin(),search.end());
        for(auto &[val, i]: search){
            int up = 0;
            if(vis[i]){
                continue;
            }
            int down = i - 1;
            int cnt = 1;
            while(down >= 0){
                if(arrs[down] % arrs[i] == 0){
                    count--;
                    cnt++;
                    if(vis[down]){
                        break;
                    } else {
                        vis[down] = true;
                    }
                } else {
                    break;
                }
                down--;
            }
            up = i + 1;
            while(up <= V - 1){
                if(arrs[up] % arrs[i] == 0){
                    count--;
                    cnt++;
                    if(vis[up]){
                        break;
                    } else {
                        vis[up] = true;
                    }
                } else {
                    break;
                }
                up++;
            }
            MST += (cnt - 1) * val;
            
        }
        MST += (count - 1) * E;
        cout << MST << nl;
    }
}