#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';
map<int,vector<int> > table;
pii two_sum(int exclude, ll target, vector<ll> &arr){
    for(int i = 0; i < arr.size(); i++){
        if(i == exclude){
            continue;
        }
        if(table.count(target-arr[i])){
            for(int value: table[target-arr[i]]){
                if(!(value == i || value == exclude)){
                    return {i + 1, value + 1};
                }
            }
        }
    }
    return {-1,-1};
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll x;
    cin >> n >> x;
    
    vector<ll> arr(n,0);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        table[arr[i]].push_back(i);
    }
    for(int i = 0; i < n; i++){
        int f = i + 1;
        ll findval = x - arr[i];
        auto [s,t] = two_sum(i,findval,arr);
        if(s == -1 || t == -1){
            continue;
        } else {
            cout << f << sp << s << sp << t << nl;
            return 0;
        }
    }
 
    cout << "IMPOSSIBLE" << nl;
 
    
 
}
