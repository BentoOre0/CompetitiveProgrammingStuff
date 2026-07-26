#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';
string s;
ll dp[301][301];
ll optimal(int L, int R){
    if(L > R){
        return 0;
    }
    if(R == L){
        return 1;
    }
    if(dp[L][R] != -1){
        return dp[L][R];
    }
    ll WC = R - L + 1;
    string sub = "";
    for(int M = L; M <= R - 1; M++){
        sub += s[M];
        int st = M + 1;
        while(true){
            if(st + sub.size() - 1 > R){
                break;
            }
            string temp = s.substr(st,sub.size());
            if(temp != sub){
                break;
            } else {
                st += sub.size();
            }
        }
        // cout << L << sp << M << sp << st  << sp << R << nl;
        WC = min(WC,optimal(L, M) + optimal(st, R));
        
    }
    return dp[L][R] = WC;
}

/*

f(i,j) = ?
f(i,j) minimum weight for this string
f(i,j) = 1 if all the same
f(i,j) = 1 if i == j
f(i,j) = 

consider i,i + k 
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while(cin >> s){
        memset(dp,-1,sizeof(dp));
        cout << optimal(0, s.size() - 1) << nl;
    }
    
    
}
