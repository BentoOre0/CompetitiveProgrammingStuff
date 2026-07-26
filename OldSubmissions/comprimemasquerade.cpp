#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
ll MOD = 998244353;
ll evaluate(vector<pll>& ballroom){
    ll total = 1;
    for(int i = 0; i < ballroom.size(); i++){
        for(int j = i+1; j < ballroom.size(); j++){
            if(gcd(ballroom[j].second,ballroom[i].second) != 1){
                return 0;
                // total += ((ballroom[j].first)%MOD * (ballroom[i].first) % MOD) % MOD;
                // total %= MOD;
            }
        }
    }
    for(int i = 0; i < ballroom.size(); i++){
        total *= ballroom[i].first;
        total %= MOD;
    }
    return total;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    if(n <= 20){
        vector<ll>arr(n,0);
        ll num;
        for(int i = 0; i < n; i++){
            cin >> num;
            arr[i] = num;
        }
        ll total = 0;
        int mask = (1 << n);
        for(int i = 1; i < mask; i++){
            int cmask = i;
            vector<pll> ballroom;
            while(cmask){
                int ls = cmask & -cmask;
                int v = __builtin_ctz(ls);
                ballroom.push_back({arr[v],v + 1});
                cmask -= ls;
            }
            ll temp = evaluate(ballroom) % MOD;
            // cout << temp << nl;
            total += temp;
            total %= MOD;
        }
        cout << total << nl;


    } else {
        cout <<"IWASNOTMADEFORTHIS" << nl;
        return 0;
    }
}
