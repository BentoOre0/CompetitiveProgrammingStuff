#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';

ll MOD = 1e9 + 7;

ll dp[500][500];
vector<vector<ll> > choosemod(251,vector<ll>(251,0));
ll f(int START, int END, string &S){
    if(START >= END){
        return 1;
    }
    if(START+1 == END){
        if(S[START] == S[END]){
            return 1;
        } else {
            return 0;
        }
    } else if(dp[START][END] != -1){
        return dp[START][END];
    } else {
        ll total = 0;
        for(int K = START; K <= END; K++){
            if((S[START] == S[K]) && ((K - START + 1) % 2 == 0) && ((END - (K + 1) + 1) % 2 == 0)){
                ll temp = (f(START+1, K-1,S) % MOD) * (f(K + 1, END,S) % MOD);
                temp %= MOD;
                ll totalpairs = (K - START + 1)/2 + (END - (K + 1) + 1)/2;
                ll leftpairs = (K - START + 1)/2;
                total += (choosemod[totalpairs][min(leftpairs, totalpairs-leftpairs)] * temp) % MOD;
                total %= MOD;
            }
        }
        return dp[START][END] = total;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    cin >> S;
    ll n = S.size();

    memset(dp,-1,sizeof(dp));
    choosemod[0][0] = 1;
    for(int i = 1; i < 251; i++){
        for(int j = 0; j < 251; j++){
            choosemod[i][j] = choosemod[i-1][j];
            choosemod[i][j] %= MOD;
            if(j - 1 >= 0){
                choosemod[i][j] += choosemod[i-1][j-1];
            }
            choosemod[i][j] %= MOD;
        }
    }
    cout << f(0, n-1, S) << nl;

    
}
