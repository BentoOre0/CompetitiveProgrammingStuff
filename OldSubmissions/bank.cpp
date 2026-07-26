#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';


ll cantor_hash(ll x, ll y){
    return (((x + y) * (x + y + 1)) >> 1) + y;
}
unordered_map<ll, vector<ll> > ks;

unordered_map<ll, bool> vis;



int pathexists(int node, int mask,vector<ll> &salary, vector<ll> &billz, vector<vector<int> > &dp){
    if(node == salary.size()){
        return 1;
    } else {
        if(dp[node][mask] != -1){
            return dp[node][mask];
        }
        int flag = 0;
        for(int kbitmask: ks[salary[node]]){
            if((mask & kbitmask) == kbitmask){
                flag = flag | pathexists(node + 1, mask ^ kbitmask,salary, billz,dp);
            }
        }
        dp[node][mask] = flag;
        return flag;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<ll> salary;
    vector<ll> billz;
    unordered_set<ll> sinit;
    ll num;
    for(int i = 0; i < N; i++){
        cin >> num;
        ks[num] = vector<ll>();
        salary.push_back(num);
        sinit.insert(num);
    }
    ll totalbillz = 0;
    for(int i = 0; i < M; i++){
        cin >> num;
        totalbillz += num;
        billz.push_back(num);
    }
    sort(billz.begin(),billz.end());
    // sort(billz.begin(),billz.end());
    for(int m = 0; m < (1 << M) - 1; m++){
        ll temp_t = 0;
        int maskcopy = m;
        while(maskcopy){
            int ls = maskcopy & -maskcopy;
            int u = __builtin_ctz(ls);
            temp_t += billz[u];
            maskcopy -= ls;
        }
        if(sinit.count(temp_t)){
            ks[temp_t].push_back(m);
        }
    }
    vector<vector<int> > dp(N,vector<int>((1 << M),-1));
    int ans = pathexists(0,(1 << M) - 1, salary, billz, dp);
    if(ans) {
        cout << "YES" << nl;
    } else {
        cout << "NO" << nl;
    }
}