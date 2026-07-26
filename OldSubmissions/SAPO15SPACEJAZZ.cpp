#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

ll dp[550][550];
ll f(int L, int R, string &S){
    if(L == R){
        return 1;
    } else if(L > R){
        return 0;
    }
    if(dp[L][R] != -1){
        return dp[L][R];
    }
    char a = S[L];
    ll count = inf;
    for(int M = L + 1; M <= R; M++){
        if(S[M] == a){
            count = min(count,f(L + 1, M - 1,S) + f(M + 1, R, S));
        }
    }
    count = min(1 + f(L + 1, R, S),count);
    return dp[L][R] = count;
}

int main() {
    memset(dp,-1,sizeof(dp)); 
    string N;
    cin >> N;
    cout << f(0, N.size() - 1, N) << nl;;
}
