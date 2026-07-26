#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';


int dp[1001][1001];
int F(int i, int j, vector<int> &a, vector<int> &b){
    if(i == 0 || j == 0){
        return 0;
    } else {
        if(dp[i][j] != -1){
            return dp[i][j];
        } else {
            if(abs(a[i - 1] - b[j - 1]) <= 4){
                return dp[i][j] = 1 + F(i - 1, j - 1,a,b);
            } else {
                return dp[i][j] = max(F(i - 1,j,a,b),F(i,j - 1,a,b));
            }
        }
    }
}

int main(){
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(dp,-1,sizeof(dp));
    int N;
    cin >> N;
    vector<int> a,b;
    int num;
    for(int i = 0; i < N; i++){
        cin >> num;
        a.push_back(num);
    }
    for(int i = 0; i < N; i++){
        cin >> num;
        b.push_back(num);
    }
    cout << F(a.size(),b.size(),a,b) << nl;
}
