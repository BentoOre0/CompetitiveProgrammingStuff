#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vii = vector<vector<int> >;
using vll = vector<vector<ll> >;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

vector<int> SN, LP, parent;
vector<bool> AP, vis;
vector<unordered_set<int> > adj;
vector<pii> BRIDGE;
int clk = 0;
void DFS_AP_BRIDGE(int num){
    vis[num] = true;
    SN[num] = clk; LP[num] = SN[num];
    clk++;
    int children = 0;
    for(int neigh: adj[num]){
        if(!vis[neigh]){
            parent[neigh] = num;
            children++;
            DFS_AP_BRIDGE(neigh);
            LP[num] = min(LP[neigh],LP[num]);
            if(parent[num] == -1 && children > 1){
                /*
                Two Subgraph Children (not necessarily SCC)
                Which means it is an articulation point
                */
                AP[num] = true;
            } 
            if(parent[num] != -1 && LP[neigh] >= SN[num]){
                //num -> neigh points to a SCC subgraph child so num is an articulation point and num -> neigh is a bridge
                AP[num] = true;
                if(SN[num] < LP[neigh]){
                    //in this case, the neighbour's LP doesn't point past to num
                    //This means num -> neigh is a bridge to a SCC
                    //if SN[num] == LP[neigh] num itself is in the SCC. This means that num -> neigh isn't a bridge.
                    BRIDGE.push_back({num, neigh});
                }
            }
        } else {
            if(neigh != parent[num]){
                LP[num] = min(LP[num], SN[neigh]);
            }
            //BACK EDGE/CROSS EDGE FOUND
            //SN of NEIGH might be lower than current LP
            //This makes sure that if we find back edge, we still update LP to find smallest case 
        }
    }
}