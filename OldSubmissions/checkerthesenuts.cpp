#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
#include<bits/stdc++.h>
using namespace std;
ll backtrack(ll rt, int p, int n, int k, vector<ll> &diff, vector<ll> &perms){
    bool ended = true;
    if(p == n){
        if(rt + diff[n] <= 0){
            return 0;
        } else {
            return 10e15;
        }
    } else {
        ll mycase = 10e15;
        ll value = rt + perms[p] + diff[p];
        //let rt be defined as sum of everything less than index p
        if(value > 0){
            //continue
            diff[p] -= value;
            diff[min(p + k,n)] += value;
            mycase = min((ll)(value + backtrack(rt + diff[p],p + 1, n, k, diff, perms)),mycase);
            diff[p] += value;
            diff[min(p + k,n)] -= value;
        } else {
            mycase = min((ll)(backtrack(rt + diff[p],p + 1, n, k, diff, perms)),mycase);
        }
        return mycase;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<ll> orig(n,0), arrange(n,0),perms(n,0);

        ll total = 0;
        for(int i = 0; i < n; i++){
            cin >> orig[i];
            total += orig[i];
        }
        for(int i = 0; i < n; i++){
            cin >> arrange[i];
        }
        for(int i = 0; i < n; i++){
            perms[i] = orig[arrange[i] - 1];
        }
        vector<ll> diffs(n+1,0);
        ll retval = backtrack(0,0,n,k,diffs,perms);
        cout << retval << nl;
    }

}