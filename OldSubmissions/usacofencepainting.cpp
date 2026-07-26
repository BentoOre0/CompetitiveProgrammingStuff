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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);                                                                 
    int a,b,c,d;
    cin >> a >> b;
    cin >> c >> d;
    

    /*
            L1      R1
        L2        R2
    */
    if(a <= d && c <= b){
        cout << max(b,d) - min(a,c) << nl;   
    } else {
        cout << b - a + d - c << nl;
    }
}    