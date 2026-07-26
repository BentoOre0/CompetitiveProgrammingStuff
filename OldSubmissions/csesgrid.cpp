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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<bool> > canvis(n, vector<bool>(n, true));
    char c;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> c;
            if(c == '*'){
                canvis[i][j] = false;
            }
        }
    }
    ll MOD = 1e9 + 7;
    vector<vector<ll> > dist(n, vector<ll>(n,0));
    if(canvis[0][0]){
        dist[0][0] = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(!canvis[i][j]){
                continue;
            }
            if(i - 1 >= 0){
                if(canvis[i - 1][j]){
                    dist[i][j] += dist[i-1][j] % MOD;
                }
            }
            dist[i][j] %= MOD;
            if(j - 1 >= 0){
                if(canvis[i][j-1]){
                    dist[i][j] += dist[i][j-1] % MOD;
                }
            }
            dist[i][j] %= MOD;
        }
    }
    cout << dist[n - 1][n-1] % MOD << nl;
}