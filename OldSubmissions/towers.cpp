#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    map<int, int> thetop;
    vector<int> arr(n,0);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++){
        auto it = thetop.upper_bound(arr[i]);
        if(it == thetop.end()){
            thetop[arr[i]]++; 
        } else {
            thetop[it->first]--;
            if(!thetop[it->first]){
                thetop.erase(it->first);
            }
            thetop[arr[i]]++;
        }
    }
    int rs = 0;
    for(auto [elem,count] : thetop){
        rs += count;
    }
    cout << rs << nl;


}
