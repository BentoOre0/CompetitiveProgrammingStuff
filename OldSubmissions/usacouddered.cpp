#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

ll f(int mask, string &s, vector<char> &wl,vector<vector<int > > &adj, vector<ll> &dp){
    if(dp[mask] != -1){
        return dp[mask];
    } else {
        if(mask == 0){
            return 1;
        }
        int maskcopy = mask;
        ll minimum = inf;
        while(maskcopy){
            int ls = maskcopy & -maskcopy;
            int i = __builtin_ctz(ls);
            ll total = 0;
            for(int j = 0; j < wl.size(); j++){
                if(mask & (1 << j)){
                    total += (ll)adj[wl[j] - 'a'][wl[i] - 'a'];
                }
            }
            minimum = min(minimum, total + f(mask ^ ls, s, wl, adj, dp));
            maskcopy -= ls;
        }
        dp[mask] = minimum;
        return dp[mask];
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    
    vector<ll> dp(1 << 20,-1);
    cin >> s;
    unordered_set<char> checkit;
    vector<vector<int> > adj(26, vector<int> (26,0));
    for(int i = 0; i < s.size() - 1; i++){
        int u = s[i] - 'a';
        int v = s[i + 1] - 'a';
        adj[u][v]++;
        checkit.insert(s[i]);
    }
    checkit.insert(s.back());
    vector<char> wl;
    for(char c: checkit){
        wl.push_back(c);
    }
    int mask = (1 << (checkit.size())) - 1;
    ll ans = f(mask,s,wl,adj,dp);
    cout << ans << nl;
    /*

    keep track of letters i haven't got yet

    everything on
    

    for all things left
    suppose I pick this letter, 
    this letter is now the first in the order
    check everything else
    dp recursion
    */
}