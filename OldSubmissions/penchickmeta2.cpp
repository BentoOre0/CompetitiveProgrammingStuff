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
    int T;
    cin >> T;
    while(T--){
        ll n, m, q, d;
        cin >> n >> m >> q >> d;
        vector<ll> E;
        ll num;
        for(int i = 0; i < n; i++){
            cin >> num;
            E.push_back(num);
        } 
        vector<ll> F;
        for(int i = 0; i < m; i++){
            cin >> num;
            F.push_back(num); 
        }

        vector<ll> newarray;
        int topE = 0, topF = 0;
        ll totalF = 0;
        ll greedysum = 0;
        int temp = 0;
        for(int i = 0; i < m && topE < n; i++){
            temp++;
            totalF += F[i];
            if(F[topF] <= E[topE]){
                greedysum += F[topF];
                topF++;
            } else {
                greedysum += E[topE];
                topE++;
            }
            if(totalF <= greedysum){
                topE = 0;
                greedysum = totalF;
                topF = i + 1;
            }
            newarray.push_back(greedysum);
        }
        while(topE != n || topF != m){
            if(topF == m){
                greedysum += E[topE];
                topE++;
            } else if(topE == n){
                greedysum += F[topF];
                topF++;
            } else {
                if(F[topF] <= E[topE]){
                    greedysum += F[topF];
                    topF++;
                } else {
                    greedysum += E[topE];
                    topE++;
                }
            }
            newarray.push_back(greedysum);
        }
     // while(topE < n){
        //     greedysum += E[topF];
        //     topE++;
        //     newarray.push_back(greedysum);
        // }
        // for(int i = 0; i < newarray.size(); i++){
        //     cout << newarray[i] << sp;
        // }
        // cout << nl;
        
        vector<ll> queries;
        ll nums;
        for(int i = 0; i < q; i++){
            cin >> nums;
            if(nums % d != 0){
                queries.push_back(nums/d + 1);
            } else {
                queries.push_back(nums/d);
            }
        }
        for(int i = 0; i < q; i++){
            if(queries[i] > newarray.size()){
                cout << "penchickdead" << sp;
            } else {
                cout << newarray[queries[i] - 1] << sp;
            }
        }
        cout << nl;
    }
}
