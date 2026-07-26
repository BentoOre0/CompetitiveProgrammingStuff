#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                                 
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';                                                           


int main(){                                                                    
    ll n, k;
    cin >> n >> k;
    vector<ll> vec;
    ll num;
    for(int i = 0; i < n; i++){
        cin >> num;
        vec.push_back(num);
    }
    ll count = 0;
    map<ll,ll> us;
    int L = 0, R = 0;
    for(int i = 0; i < n; i++){
        us[vec[i]]++;
        // cout << L << sp << R << nl;
        if(us.size() > k){
            while(us.size() > k){
                us[vec[L]]--;
                if(us[vec[L]] == 0){
                    us.erase(vec[L]);
                }
                L++;
            }
        }
        R++;
        
        count += (R - L);
    }
    cout << count << nl;
    

}    