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
    ll MOD = 1e9 + 7;
    ll n, x, k;
    cin >> n;
    map<int,int> pf;
    ll prime, exp;
    for(int i = 0; i < n; i++){
        cin >> prime >> exp;
        pf[prime] = exp;
    }
    ll number_of_fac = 1;
    ll number_of_fac_2 = 1;

    bool found_even = false;
    for(auto &[base, exp] : pf){
        number_of_fac *= ((exp + 1) % MOD);
        if(!found_even && ((exp + 1) % 2 == 0)){
            found_even = true;
            number_of_fac_2 *= (((exp + 1) >> 1) % (MOD - 1));
        } else {
            number_of_fac_2 *= ((exp + 1) % (MOD - 1));
        }
        number_of_fac %= MOD;
        number_of_fac_2 %= (MOD - 1);
    }
    cout << number_of_fac % MOD << sp;
    ll sum_of_fac = 1;
    for(auto &[base, exp] : pf){
        ll sum = 0;
        ll curr_pow = 1;
        sum_of_fac *= (modpow(base, exp + 1, MOD) - 1);
        sum_of_fac %= MOD;
        sum_of_fac *= modpow(base - 1, MOD - 2, MOD);
        sum_of_fac %= MOD;
    }
    cout << sum_of_fac % MOD << sp;

    ll number = 1;
    // number_of_fac_2 *= modpow(2,500000001, MOD - 1);
    number_of_fac_2 %= MOD - 1;
    for(auto &[base, exp]: pf){
        if(!found_even){
            number *= modpow(base, exp >> 1, MOD);   
        } else {
            number *= modpow(base, exp, MOD);
        }
        number %= MOD;
    }
    number = modpow(number, number_of_fac_2, MOD);
    cout << number % MOD << nl;
}    