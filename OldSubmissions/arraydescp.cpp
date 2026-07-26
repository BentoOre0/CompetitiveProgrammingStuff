#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

int dp[100001][101];
int MOD = 1e9 + 7;
int f(int id, int currvalue, int m, vector<int> &arr){
    if(id == arr.size() - 1){
        return 1;
    } else {
        if(dp[id][currvalue] != -1){
            return dp[id][currvalue];
        } else {
            if(arr[id + 1] == 0){
                int count = 0;
                if(currvalue + 1 <= m){
                    count += f(id + 1, currvalue + 1,m,arr);
                    count %= MOD;
                }
                if(currvalue - 1 >= 1){
                    count += f(id + 1, currvalue - 1,m,arr);
                    count %= MOD;
                }
                count += f(id + 1, currvalue,m,arr);
                count %= MOD;
                dp[id][currvalue] = count;
                return count;
            } else if(abs(arr[id + 1] - currvalue) <= 1){
                return dp[id][currvalue] = f(id + 1, arr[id + 1], m, arr) % MOD;
            } else {
                // cout << id << sp << currvalue << nl;
                return dp[id][currvalue] = 0;
            }
        }
    }
}
int main() {
    int n,m;
    cin >> n >> m;
    memset(dp,-1,sizeof(dp));
    vector<int> arr;
    int num;
    for(int i = 0; i < n; i++){
        cin >> num;
        arr.push_back(num);
    }
    if(arr[0] == 0){
        int count = 0;
        for(int i = 1; i <= m; i++){
            count += f(0,i,m, arr);
            count %= MOD;
        }
        cout << count % MOD << nl;
    } else {
        cout << f(0,arr[0], m, arr) % MOD << nl;
    }

}
