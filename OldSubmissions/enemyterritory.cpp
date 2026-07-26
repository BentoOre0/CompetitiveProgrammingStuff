#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
int dis(const pii &a, const pii &b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

pii mins(const vector<pii> &enemies, int L, int R, const pii &cord){
    if (R - L == 1) {
        return enemies[L];
    } else if (R - L == 2) {
        return (dis(enemies[L], cord) < dis(enemies[R - 1], cord)) ? enemies[L] : enemies[R - 1];
    } else {
        int mid = (L + R) >> 1;
        pii half1 = mins(enemies, L, mid, cord);
        pii half2 = mins(enemies, mid, R, cord);
        return (dis(half1, cord) < dis(half2, cord)) ? half1 : half2;
    }
}

void generateDistanceGrid(vector<vector<int>> &dist, const vector<pii> &enemies, int XX, int YY){
    queue<pii> Q;
    for(auto elem: enemies){
        Q.push(elem);
        dist[elem.first][elem.second] = 0;
    }
    while(!Q.empty()){
        auto [nx, ny] = Q.front(); Q.pop();
        for (int k = 0; k < 4; ++k) {
            int x = nx + dx[k], y = ny + dy[k];
            if (x >= 0 && x < XX && y >= 0 && y < YY) {
                if(dist[x][y] == inf){
                    Q.push({x,y});
                }
                dist[x][y] = min(dist[nx][ny] + 1, dist[x][y]);
                // Q.push({x,y});
            }
        }
    }
    // for (int i = 0; i < XX; ++i) {
    //     for (int j = 0; j < YY; ++j) {
    //         pii temporary = {i, j};
    //         pii closestEnemy = mins(enemies, 0, enemies.size(), temporary);
    //         dist[i][j] = dis(closestEnemy, temporary);
    //     }
    // }
}

int bfs(const vector<vector<int>> &dist, int XX, int YY, int sx, int sy, int ex, int ey, int minDist) {
    
    vector<vector<int>> vis(XX, vector<int>(YY, inf));
    queue<pii> Q;
    Q.push({sx, sy});
    vis[sx][sy] = 0;

    while (!Q.empty()) {
        auto [nx, ny] = Q.front(); Q.pop();
        for (int k = 0; k < 4; ++k) {
            int x = nx + dx[k], y = ny + dy[k];
            if (x >= 0 && x < XX && y >= 0 && y < YY && dist[x][y] >= minDist && vis[x][y] == inf) {
                vis[x][y] = vis[nx][ny] + 1;
                Q.push({x, y});
            }
        }
    }
    return vis[ex][ey];
}

int binarySearchMaxSafeDistance(const vector<vector<int>> &dist, int XX, int YY, int sx, int sy, int ex, int ey){
    int high = dist[sx][sy] + 1;
    int low = 0;
    int wc;

    while (high - low >= 2) {
        int mid = (low + high) / 2;
        wc = bfs(dist, XX, YY, sx, sy, ex, ey, mid);
        if (wc == inf) {
            high = mid;
        } else {
            low = mid;
        }
    }

    wc = bfs(dist, XX, YY, sx, sy, ex, ey, low);
    return low;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, XX, YY;
    cin >> N >> XX >> YY;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    vector<pii> enemies(N);
    for (int i = 0; i < N; ++i) {
        cin >> enemies[i].first >> enemies[i].second;
    }

    vector<vector<int>> dist(XX, vector<int>(YY, inf));
    generateDistanceGrid(dist, enemies, XX, YY);

    int maxSafeDistance = binarySearchMaxSafeDistance(dist, XX, YY, sx, sy, ex, ey);
    int minPathLength = bfs(dist, XX, YY, sx, sy, ex, ey, maxSafeDistance);

    cout << maxSafeDistance << sp << minPathLength << nl;
}
