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

ll modpow(ll base, ll exp){
    if (exp == 1){
        return base % MOD;
    }
    if (exp == 0){
        return 1;
    }
    if(exp % 2 == 1){
        return ((base) * modpow(base, exp - 1)) % MOD;
    } else {
        ll temp = modpow(base, exp >> 1);
        temp %= MOD;
        return (temp * temp) % MOD;
    }
}
int main(){                                                                    
    ios::sync_with_stdio(false);                                                
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        ll a, b;
        cin >> a >> b;
        cout << modpow(a,b) << nl;
    }
}    