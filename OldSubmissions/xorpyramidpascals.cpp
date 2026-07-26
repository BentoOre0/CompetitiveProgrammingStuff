#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                     
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<ll> twoexp(2e5+1,0);
    for(int i = 2; i <= 2e5; i++){
        int num = i;
        int LS = num & -num;
        int powsof2 = __builtin_ctz(LS);
        twoexp[i] = powsof2;
    }
    vector<ll> facttwoexp(2e5+1,0);
    for(int i = 1; i <= 2e5; i++){
        facttwoexp[i] += facttwoexp[i - 1] + twoexp[i];
    }

    ll n;
    cin >> n;
    vector<ll> vec;
    vector<ll> coeff;
    ll num;
    for(int i = 0; i < n; i++){
        cin >> num;
        vec.push_back(num);
    }
    ll total = 0;
    for(int i = 0; i <= n; i++){
        if(facttwoexp[n - 1] - (facttwoexp[i] + facttwoexp[n - 1 - i]) == 0){
            total ^= vec[i];
        }
    }
    cout << total << nl;
}