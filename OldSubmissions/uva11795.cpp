#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';
ll tsp(int v, int mask, vector<int> &moves, vector<vector<ll> > &dp){
    if(mask == 0){
        return 1;
    } else {
        if(dp[v][mask] != -1){
            return dp[v][mask];
        } else {
            int move_mask = moves[mask];
            int maskcopy = mask;
            ll paths = 0;
            while(maskcopy){
                int ls = maskcopy & -maskcopy;
                int id = __builtin_ctz(ls);
                if(move_mask & (1 << id)){
                    paths += tsp(id + 1,mask - ls,moves,dp);
                }
                maskcopy -= ls;
            }
            dp[v][mask] = paths;
            return dp[v][mask];
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    int cs = 1;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        vector<int> adj, moves(1 << N,0);
        vector<vector<ll> > dp(17,vector<ll>(66000,-1));
        for(int i = 0; i <= N; i++){
            int total = 0;
            char c;
            for(int j = 1; j <= N; j++){
                cin >> c;
                int num = c - '0';
                total += ((int)pow(2,(j-1))) * num;
            }
            adj.push_back(total);
        }
        int tspmask = (1 << (N)) - 1;
        //compress it based 
        for(int mask = 0; mask <= (1 << (N)) - 1; mask++){
            int maskreach = adj[0];
            for(int i = 1; i <= N; i++){
                if(!(mask & (1 << (i - 1)))){
                    maskreach = maskreach | adj[i];
                }
            }
            moves[mask] = maskreach;
        }
        ll paths = tsp(0,tspmask,moves,dp);
        cout << "Case " << cs << ": " << paths << nl;
        cs++;
    }
}
