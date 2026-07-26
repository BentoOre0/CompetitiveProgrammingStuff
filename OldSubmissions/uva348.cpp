#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

ll dp[100][100];
map<pii,pair<pii,pii> > bestcase;
ll f(int L, int R, vector<pll> &matrs){
    if(L >= R){
        return 0;
    } else if(R - L == 1){
        ll multiplications = matrs[L].first * matrs[L].second * matrs[R].second;
        return multiplications;
    } else {
        if(dp[L][R] != -1){
            return dp[L][R];
        } else {
            ll cost = (ll)inf;
            pii half1,half2;
            for(int M = L; M <= R - 1; M++){
                ll temp = f(L,M,matrs) + f(M + 1,R,matrs) + matrs[L].first * matrs[M].second * matrs[R].second;
                if(temp <= cost){
                    half1 = {L,M};
                    half2 = {M+1,R};
                    cost = temp;
                }
            }
            if(cost == (ll)inf){
                // cout << L << sp << R << nl;
            } else {
                bestcase[{L,R}] = {half1,half2};
            }
            dp[L][R] = cost;
            return dp[L][R];
        }
    }   
}

string reconstruct(pii &node){
    int a = node.first;
    int b = node.second;
    if(abs(a - b) == 1){
        string s = "(A";
        s += to_string(a + 1);
        s += " x A"; 
        s += to_string(b + 1);
        s += ")";
        return s;
    } else if(a == b){
        string s = "A";
        s += to_string(a + 1);
        return s;
    } else {
        auto [left,right] = bestcase[node];
        string s = "(";
        s += reconstruct(left);
        s += " x ";
        s += reconstruct(right);
        s += ")";
        return s;
    }
}
int main() { 
    int cs = 1;
    while(true){
        int n;
        cin >> n;
        if(n == 0){
            break;
        }
        memset(dp,-1,sizeof(dp));
        bestcase.clear();
        vector<pll> matrs;
        for(int i = 0; i < n; i++){
            int r,c;
            cin >> r >> c;
            matrs.push_back({r,c});
        }
        
        
        f(0, n - 1, matrs);
        pii ans = {0,n-1};
        
        cout << "Case " <<cs << ": "<< reconstruct(ans) << nl;
        cs++;
    }
}
