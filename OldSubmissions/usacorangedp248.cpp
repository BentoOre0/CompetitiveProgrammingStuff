#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

int dp[300][300];
int f(int L, int R, vector<int> &arr){
    if(L > R){
        return 0;
    }
    if(dp[L][R]!= -1){
        return dp[L][R];
    }
    if(R == L){
        return arr[L];
    }
    int mx = -999999;
    for(int M = L + 1; M <= R; M++){
        int left = f(L, M - 1, arr);
        int right = f(M, R, arr);
        if(left == right && left != 0){
            mx = max(left + 1, mx);
        }
    }
    return dp[L][R] = mx;
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    memset(dp,-1,sizeof(dp));
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int N;
    cin >> N;
    vector<int> arr(N);
    
    for(int i = 0; i < N; i++){
        cin >> arr[i];    
    }
    int maxResult = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            maxResult = max(maxResult, f(i, j,arr));
        }
    }
    cout << maxResult << nl;

}
