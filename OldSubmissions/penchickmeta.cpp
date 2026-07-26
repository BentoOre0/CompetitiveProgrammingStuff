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
        while(topE < n && topF < m){
            if(F[topF] <= E[topE]){
                newarray.push_back(F[topF]);
                topF++;
            } else {
                newarray.push_back(E[topE]);
                topE++;
            }
        }

        while(topE < n){
            newarray.push_back(E[topE]);
            topE++;
        }
        while(topF < m){
            newarray.push_back(F[topF]);
            topF++;
        }
        ll temp = 0;
        vector<ll> runningtotal;
        for(int i = 0; i < m + n; i++){
            runningtotal.push_back(temp + newarray[i]);
            temp += newarray[i];
        }
        
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
            if(queries[i] > runningtotal.size()){
                cout << "penchickdead" << sp;
            } else {
                cout << runningtotal[queries[i] - 1] << sp;
            }
        }
        cout << nl;

        
    }
}
