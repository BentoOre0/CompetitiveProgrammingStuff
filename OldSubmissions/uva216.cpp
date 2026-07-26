#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

double dp[8][256];
double ham(int node, int mask, vector<vector<double> > &graph){
    if(mask == 0){
        return 0;
    } else {
        if(dp[node][mask] != -1.0){
            return dp[node][mask];
        } else {
            double ans = (double)inf;
            int m = mask;
            while(m){
                int ls = m & -m;
                int v = __builtin_ctz(ls);
                if(graph[node][v] != (double) inf){
                    if(graph[node][v] + ham(v,mask ^ ls,graph) < ans){
                        ans = graph[node][v] + ham(v,mask ^ ls,graph);
                    }
                }
                m -= ls;
            }
            dp[node][mask] = ans;
            return ans;
        }
    }
}
double distance(pii a, pii b){
    double ax = a.first, ay = a.second, bx = b.first, by = b.second;
    return sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    int ct = 1;
    cout << fixed << setprecision(2);
    while(true){
        cin >> N;
        if(N != 0){
            if(ct != 1){
                cout << nl;
            }
            fill(dp[0],dp[0] + 2048, -1.0);
            vector<vector<double> > graph(N, vector<double>(N,0.0));
            vector<pii> edgelist(N);
            int x,y;
            for(int i = 0; i < N; i++){
                graph[i][i] = 0.0;
                cin >> x >> y;
                edgelist[i] = {x,y};
            }
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    if(i != j){
                        graph[i][j] = distance(edgelist[i],edgelist[j]) + 16;
                    } else {
                        graph[i][j] = 0.0;
                    }
                }
            }
            int mask = ((1 << (N)) - 1) ^ 1;
            int minstart = 0;
            auto pathlength = ham(0,mask,graph);
            for(int i = 1; i < N; i++){
                mask = ((1 << (N)) - 1) ^ (1 << i);
                auto pld = ham(i,mask,graph);
                if(pld < pathlength){
                    minstart = i;
                    pathlength = pld;
                }
            }
            // cout << pathlength <<nl;
            cout << "**********************************************************" << nl;
            cout << "Network #" << ct << nl;
            int nod = minstart;
            int tmask = ((1 << N) - 1) ^ (1 << minstart);
            vector<int> tsppath; tsppath.push_back(minstart);
            for(int i = 0; i < N - 1; i++){
                double toprint = inf;
                int nextnod = -1;
                int u = tsppath[i];
                int maskcopy = tmask;
                while(maskcopy){
                    int ls = maskcopy & -maskcopy;
                    int v = __builtin_ctz(ls);
                    if(tmask & (1 << v)){
                        if(graph[u][v] + dp[v][tmask ^ (1 << v)] < toprint){
                            toprint = graph[u][v] + dp[v][tmask ^ (1 << v)];
                            nextnod = v;
                        }
                    }
                    maskcopy -= ls;
                }
                tsppath.push_back(nextnod);
                tmask ^= (1 << (nextnod));
            }
            if(tsppath.size() % 2){
                reverse(tsppath.begin(),tsppath.end());
            }
            
            
            for(int i = 0; i < tsppath.size() - 1; i++){
                auto cord1 = edgelist[tsppath[i]];
                auto cord2 = edgelist[tsppath[i + 1]];
                int x1 = cord1.first, y1 = cord1.second, x2 = cord2.first, y2 = cord2.second;
                cout << "Cable requirement to connect (" << (int)x1 << "," << (int)y1 <<") to (" << (int)x2 << "," << (int)y2 << ") is " << graph[tsppath[i]][tsppath[i + 1]] << " feet." << nl;
            }
            cout << "Number of feet of cable required is " << pathlength << ".";
            ct++;
        } else {
            cout << nl;
            break;
        }
    }
}
