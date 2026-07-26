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

ll dp[1002][1002];
ll f(int i, int j, string &a, string &b){
    if(i < 0 || j < 0){
        return 0;
    } else {
        if(dp[i][j] != -1){
            return dp[i][j];
        } else {
            if(a[i] == b[j]){
                dp[i][j] = 1 + f(i - 1, j - 1, a,b);
            }  else {
                dp[i][j] = max(f(i-1,j,a,b), f(i,j-1,a,b));
            }
            return dp[i][j];
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    int count = 0;
    while(getline(cin,a)&&getline(cin,b)){
        for(int i = 0; i < 1002; i++){
            for(int j = 0; j < 1002; j++){
                dp[i][j] = -1;
            }
        }
        ll answer = f((int)a.size() - 1, (int)b.size() - 1,a,b);
        cout << answer;
        cout << nl;
    }
}