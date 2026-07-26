#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                                 
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           


ll modpow(ll base, ll exp, ll md){
    if (exp == 1){
        return base % md;
    }
    if (exp == 0){
        return 1;
    }
    if(exp % 2 == 1){
        return ((base) * modpow(base, exp - 1, md)) % md;
    } else {
        ll temp = modpow(base, exp >> 1, md);
        temp %= md;
        return (temp * temp) % md;
    }
}
int main(){                                                                    
    ios::sync_with_stdio(false);                                                
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<ll> n_fac_mod(1e6 + 1,1);
    vector<ll> inv_mod(1e6 + 1,1);
    ll MOD = 1e9 + 7;
    for(ll i = 1; i <= 1e6; i++){
        n_fac_mod[i] = (n_fac_mod[i - 1] * i) % MOD;
    }
    inv_mod[1e6] = modpow(n_fac_mod[1e6], MOD -2, MOD);
    for(ll i = 1e6 - 1; i >= 0; i--){
        inv_mod[i] = (inv_mod[i + 1] * (i + 1)) % MOD;
    }
    
    while(t--){
        ll n, k;
        cin >> n >> k;
        cout << (((n_fac_mod[n] * inv_mod[n-k]) % MOD) * inv_mod[k]) % MOD << nl;
    }
}    