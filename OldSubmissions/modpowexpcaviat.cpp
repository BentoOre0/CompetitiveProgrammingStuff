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
    while(t--){
        ll a, b, c;
        cin >> a >> b >> c;
        ll MOD = 1e9 + 7;
        ll new_exp = modpow(b,c, MOD - 1);
        cout << modpow(a,new_exp,MOD) << nl;
    }
}    