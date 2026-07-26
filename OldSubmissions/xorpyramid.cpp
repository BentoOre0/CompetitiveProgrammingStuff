#include <bits/stdc++.h>                                                        
using namespace std;                                                            
using ll = long long;                                                           
using pii = pair<int,int>;                                                      
using pll = pair<long long int, long long int>;                     
const int inf = numeric_limits<int>::max();                                     
const ll INF = numeric_limits<ll>::max();                                       
const char sp = ' ';                                                            
const char nl = '\n';

//let k be 2^k
/*

Binary Jumping of sorts

f(0,0) = f(2^k, 0) ^ f(2^k,1) ^ ... ^ f(2^k, 2^k);
f(0,0) = f(1, 0)

anything that is perfect power of 2 is just xor of everything

proof by observation...
 */


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    vector<ll> vec;
    ll num;
    for(int i = 0; i < n; i++){
        cin >> num;
        vec.push_back(num);
    }

    vector<ll> temp;
    while(true){
        ll val = 0;
        ll slidingwindowsize;
        for(ll i = 18; i >= 0; i--){
            if((1 << i) <= vec.size()){
                slidingwindowsize = (1 << i);
                break;
            }
        } 
        int L = 0, R = slidingwindowsize;
        for(int i = 0; i < slidingwindowsize; i++){
            val ^= vec[i];
        }
        temp.push_back(val);
        for(R; R < vec.size(); R++){
            val ^= vec[L];
            L++;
            if(R < vec.size()){
                val ^= vec[R];
            }
            temp.push_back(val);
        }
        if(temp.size() == 1){
            cout << temp[0] << nl;
            break;
        } else {
            swap(temp,vec);
            temp.clear();
        }
    }
}


//what I used to find it
// int t;
    // cin >> t;
    // while(t--){
    //     int n;
    //     cin >> n;
    //     vector<ll> vec;
    //     ll num;
    //     for(int i = 0; i < n; i++){
    //         vec.push_back((ll)(1 << i));
    //     }
    //     vector<ll> temp;
    //     while(true){
    //         for(ll i = 0; i < vec.size() - 1; i++){
    //             temp.push_back(vec[i] ^ vec[i + 1]);
    //         }
    //         if(temp.size() == 1){
    //             cout << n << sp;
    //             for(ll i = 0; i < n; i++){
    //                 if(temp[0] & (1 << i)){
    //                     cout << 1;
    //                 } else {
    //                     cout << 0;
    //                 }
    //             }
    //             cout << nl;
    //             break;
    //         } else {
    //             swap(temp,vec);
    //             temp.clear();
    //         }
    //     }
    // }