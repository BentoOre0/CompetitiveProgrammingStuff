#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
#define FOR(L, R) for(int i = L; i < R; ++i)
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// #define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

ll dp[1001][1001][2];

vector<pii> H, G;

ll distance(pii &a, pii &b){
    return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}


ll f(int i, int j, int onanH){
    //completely explored G
    if(i == H.size() - 1 && j == G.size() && onanH){
        return 0;
    }
    if(dp[i][j][onanH] != -1){
        return dp[i][j][onanH];
    } else {
        ll temp = inf,temp2 = inf;
        if(onanH){
            if(!(i + 1 == H.size() - 1 && j != G.size())){
                if(i + 1 <= H.size() - 1){
                    temp = distance(H[i], H[i + 1]) + f(i + 1, j, 1);
                }
            }
            if(j != G.size()){
                temp2 = distance(H[i], G[j]) + f(i+1, j, 0);
            }
            return dp[i][j][onanH] = min(temp,temp2);
        } else {
            if(j != G.size() - 1){
                temp2 = distance(G[j], G[j + 1]) + f(i, j + 1, 0);
            }
            if(i != H.size()){
                temp = distance(G[j], H[i]) + f(i, j+1, 1);
            }
            return dp[i][j][onanH] = min(temp,temp2);
        }
    }
}
int main(){
    // for submission to USACO, add this
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
// interface with the input as normal
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    pii root;
    int rx,ry;
    cin >> rx >> ry;
    n--;
    int xx,yy;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < n; i++){
        cin >> xx >> yy;
        H.push_back({xx,yy});
    }
    for(int i = 0; i < m; i++){
        cin >> xx >> yy;
        G.push_back({xx,yy});
    }
    root = {rx,ry};
    std::cout << min(distance(root, H[0]) + f(0,0,1),distance(root, G[0]) + f(0,0,0)) << nl;
    
}