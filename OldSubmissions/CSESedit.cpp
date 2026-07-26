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
ll dp[5001][5001];
ll f(int i, int j, string &a, string &b){
    if(j < 0){
        return i + 1;
    } else if(i < 0){
        return j + 1;
    } else {
        if(dp[i][j] != -1){
            return dp[i][j];
        } else {
            if(a[i] == b[j]){
                return dp[i][j] = f(i - 1, j - 1, a,b);
            } else {
                return dp[i][j] = 1 + min(min(f(i - 1,j,a,b), f(i,j-1,a,b)), f(i-1,j-1,a,b));
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string n,m;
    memset(dp,-1,sizeof(dp));
    cin >> n >> m;
    cout << f(n.size() - 1, m.size() - 1, n,m) << nl;
}