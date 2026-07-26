#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
#include<bits/stdc++.h> 
using namespace std; 
// ll DNC(int i, int j, int n, vector<ll> perms){
//     // claim if I have a 0, partition it's left and right segments and find the best case
//     /*
//     1 1 5 1 1
//     0 0 4 1 1

//     1 0 3 0 1
    
//     1 5 1 1 1
//     0 3 0 1 1

//     2 1 5 1 1
//     1 0 4 1 1
//     */

// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<ll> orig(n,0), arrange(n,0),perms(n,0);
        
        ll total = 0;
        for(int i = 0; i < n; i++){
            cin >> orig[i];
            total += orig[i];
        }
        for(int i = 0; i < n; i++){
            cin >> arrange[i];
        }
        for(int i = 0; i < n; i++){
            perms[i] = orig[arrange[i] - 1];
        }
        ll totalchars = 0;
        while(true){
            bool allzero = true;
            for(int i = 0; i < n; i++){
                // cout << perms[i] << sp;
                if(perms[i] != 0){
                    allzero = false;
                }
            }
            // cout << nl;
            if(allzero){
                break;
            }
            /*
            change everything into the following
            (INDEXSTART, MAX_ELEM_IN_SUBSEGMENT,MIN_ELEM_IN SUBSEGMENT)
            */
            int bestid = n-1;
            ll global_total = 0;
            ll global_minimum = INF;
            for(int i = 0; i < n; i++){
                ll total = 0;
                ll minimum = INF;
                int id = i;
                for(int j = i; j < min(n,i+k); j++){
                    if(perms[j] == 0){
                        continue;
                    }
                    total += perms[j];
                    minimum = min(perms[j],minimum);
                }
                if(minimum < global_minimum){
                    global_total = total;
                    global_minimum = minimum;
                    bestid = id;
                } else if(minimum == global_minimum){
                    if(global_total < total){
                        global_total = total;
                        bestid = id;
                    }
                }
            }

            // cout << global_total << sp << global_minimum << sp << bestid << nl;

            totalchars += global_minimum;
            for(int i = bestid; i < min(n,bestid+k);i++){
                perms[i] -= global_minimum;
                perms[i] = max((ll)0,perms[i]);
            }
        }
        cout << totalchars << nl;
        
    }

}