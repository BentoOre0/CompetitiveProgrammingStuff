#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';


/*

10
2  4  7

*/

int dp[1001][1001];
int f(int L, int R, vector<int> &cuts){
    if(dp[L][R] != -1){
        return dp[L][R];
    } else {
        int cost = 100000;
        for(int cuttingpoint: cuts){
            if(cuttingpoint > L && cuttingpoint < R){
                cost = min(cost, R - L + f(L,cuttingpoint,cuts) + f(cuttingpoint,R,cuts));
            }
        }
        if(cost == 100000){
            cost = 0;
        }
        return dp[L][R] = cost;
    }
}

int main() { 
    while(true){
        int length;
        cin >> length;
        if(length == 0){
            break;
        }
        memset(dp,-1,sizeof(dp));
        int n;
        cin >> n;
        vector<int> cuts;
        int value;
        for(int i = 0; i < n; i++){
            cin >> value;
            cuts.push_back(value);
        }
        cout << "The minimum cutting is" << sp << f(0,length,cuts) << '.' << nl;
    }
    
    
}
