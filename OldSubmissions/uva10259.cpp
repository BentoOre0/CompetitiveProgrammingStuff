#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

void topsort(int x, int y, int k, int n, vector<vector<bool> > &vis,vector<vector<int> > &grid, vector<pii> &ts){
    vis[x][y] = true;
    for(int xi = max(0,x - k); xi <= min(n - 1, x + k); xi++){
        if(xi != x){
            if(!vis[xi][y]){
                if(grid[x][y] < grid[xi][y]){
                    topsort(xi,y,k,n,vis,grid,ts);
                }
            }
        }
    }
    for(int yi = max(0,y - k); yi <= min(n - 1, y + k); yi++){
        if(yi != y){
            if(!vis[x][yi]){
                if(grid[x][y] < grid[x][yi]){
                    topsort(x,yi,k,n,vis,grid,ts);
                }
            }
        }
    }
    ts.push_back({x,y});
    // cout << x << sp << y << nl;
}
int main() {
    int T;
    cin >> T;
    for(int tt = 0; tt < T; tt++){
        cin.ignore();
        int n, k;
        cin >> n >> k;
        vector<vector<int> > grid(n, vector<int>(n,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> grid[i][j];          
            }
        }
        vector<pii> ts;
        vector<vector<bool> > vis(n, vector<bool> (n,false));
        topsort(0,0,k,n,vis,grid,ts);
        reverse(ts.begin(),ts.end());
        vector<vector<int> > dist(n,vector<int> (n,0));
        vector<vector<bool> > vis2(n, vector<bool> (n,false));

        dist[0][0] = grid[0][0];
        for(auto &[node_x, node_y]: ts){
            // cout << node_x << sp << node_y << nl;
            vis2[node_x][node_y] = true;
            for(int xi = max(0,node_x - k); xi <= min(n - 1, node_x + k); xi++){
                if(xi == node_x){
                    continue;
                }
                if(grid[node_x][node_y] < grid[xi][node_y]){
                    if(!vis2[xi][node_y]){
                        dist[xi][node_y] = max(dist[node_x][node_y] + grid[xi][node_y], dist[xi][node_y]);
                    }
                }
            }

            for(int yi = max(0,node_y - k); yi <= min(n - 1, node_y + k); yi++){
                if(yi == node_y){
                    continue;
                }
                if(grid[node_x][node_y] < grid[node_x][yi]){
                    if(!vis2[node_x][yi]){
                        dist[node_x][yi] = max(dist[node_x][node_y] + grid[node_x][yi], dist[node_x][yi]);       
                    }
                }
            }
            
        }
        int mx = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                // cout << dist[i][j] << sp;
                mx = max(dist[i][j],mx);;
            }
            // cout << nl;
        }
        cout << mx << nl;
        if(tt != T - 1){
            cout << nl;
        }

    }
}