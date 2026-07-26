#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';


int dp[301][301];

int f(int L, int R, vector<int> &cols){
    if(L == R){
        return 1;
    } else if(L > R){
        return 0;
    }
    if(dp[L][R] != -1){
        return dp[L][R];
    }
    if(cols[L] == cols[R]){
        return f(L, R - 1, cols);
    } else {
        int cost = 9999;
        for(int M = L; M <= R - 1;M++){
            cost = min(f(L,M,cols) + f(M + 1, R, cols), cost);
        }
        return dp[L][R] = cost;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    memset(dp,-1,sizeof(dp));
    vector<int> cols(N,0);
    int num;
    for(int i = 0; i < N; i++){
        cin >> num;
        cols[i] = num;
    }
    cout << f(0, N - 1,cols) << nl;
}
