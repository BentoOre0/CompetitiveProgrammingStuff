#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
int hsh(int x, int y, int r, int c){
    return c*x + y;
}
vector<int> dx = {0,0,1,-1};
vector<int> dy = {1,-1,0,0};
vector<vector<bool> > vis;

ll solve(vector<vector<int> > &move,vector<ll> &dist, int a, int b, int r, int c, int k){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            vis[i][j] = false;
        }
    }
    for(int i = 0; i < r*c; i++){
        dist[i] = inf;
    }
    // cout << hsh(a,b,r,c) << nl;
    // cout << a << sp << b << sp << r << sp << c << nl;
    // return 0;
    dist[hsh(a,b,r,c)] = 0;
    queue<pii> Q;
    Q.push({a,b});
    while(Q.size()){
        auto &[u,v] = Q.front(); Q.pop();
        if(!vis[u][v]){
            vis[u][v] = true;
            int movemask = move[u][v];
            if(movemask & 8){
                if(!vis[u-1][v]){
                    dist[hsh(u - 1,v,r,c)] = min(dist[hsh(u - 1,v,r,c)], dist[hsh(u,v,r,c)] + 1);
                    Q.push({u-1,v});
                }
            }
            if(movemask & 4){
                if(!vis[u+1][v]){
                    dist[hsh(u + 1,v,r,c)] = min(dist[hsh(u + 1,v,r,c)], dist[hsh(u,v,r,c)] + 1);
                    Q.push({u+1,v});
                }
            }
            if(movemask & 2){
                if(!vis[u][v+1]){
                    dist[hsh(u,v + 1,r,c)] = min(dist[hsh(u,v + 1,r,c)], dist[hsh(u,v,r,c)] + 1);
                    Q.push({u,v+1});
                }
            }
            if(movemask & 1){
                if(!vis[u][v-1]){
                    dist[hsh(u,v - 1,r,c)] = min(dist[hsh(u,v - 1,r,c)], dist[hsh(u,v,r,c)] + 1);
                    Q.push({u,v-1});
                }
            }
        }
    }
    sort(dist.rbegin(),dist.rend());
    return dist[k - 1];

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c, k;
    cin >> r >> c >> k;
    // cout << r << sp << c << sp << k << nl;
    vector<vector<char> > grid(2*r+1, vector<char>(2*c+1,'+'));
    cin.ignore();
    string s;
    for(int i = 0; i < 2*r + 1; i++){
        getline(cin,s);
        for(int j = 0; j < 2*c + 1; j++){
            if(s[j] == ' '){
                grid[i][j] = '.';
            } else {
                grid[i][j] = s[j];
            }
        }
    }
    
    /*
    1 1 1 1
    N S E W
    */
    vector<vector<int> > move(r, vector<int>(c, 0));
    /*
    1 1 => 0 0
    1 3 => 0 1
    */
    int p = 0,q = 0;
    for(int i = 1; i < 2*r + 1; i += 2){
        for(int j = 1; j < 2*c + 1; j += 2){
            int movemask = 0;
            if(grid[i - 1][j] == '.'){
                movemask += 8;
            }
            if(grid[i + 1][j] == '.'){
                movemask += 4;
            }
            if(grid[i][j + 1] == '.'){
                movemask += 2;
            }
            if(grid[i][j - 1] == '.'){
                movemask += 1;
            }
            // cout << movemask << nl;
            // cout << i <<sp << j << nl;
            move[p][q] = movemask;
            // cout << p << sp << q << nl;
            q++;
            q %= c;
        }
        p++;
        
    }
    // int count = 0;
    vector<vector<ll> > answer(r, vector<ll>(c,0));
    vector<ll> dist;
    dist.resize(r*c);
    vis.resize(r,vector<bool>(c,false));
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            ll bruh = solve(move,dist,i,j,r,c,k);
            answer[i][j] = bruh;
            cout << answer[i][j];
            if(j == c - 1){
                cout << nl;
            } else {
                cout << sp;
            }
        }
    }
}