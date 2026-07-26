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
    int n;
    cin >> n;
    vector<ll> vec;
    ll num;
    for(int i = 0; i < n; i++){
        cin >> num;
        vec.push_back(num);
    }
    //sliding window
    stack<pll> s;
    s.push({0,-1});
    for(int i = 0; i < n; i++){
        while(s.top().first >= vec[i]){
            s.pop();
        }
        cout << s.top().second + 1 << sp;
        s.push({vec[i],i});
    }
}    