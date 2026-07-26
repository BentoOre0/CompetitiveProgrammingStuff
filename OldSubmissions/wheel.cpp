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
    int n, x;
    cin >> n >> x;
    vector<int> kid;
    map<int,int> kidlist;
    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        kid.push_back(num);
        kidlist[num]++;
    }
    kidlist[0] = n;
    sort(kid.begin(), kid.end());
    int cnt = 0;
    auto it = kidlist.begin();
    for(int i = 0; i < kid.size(); i++){
        int elem = kid[i];
        if(!kidlist.count(elem)){
            continue;
        }
        kidlist[elem]--;
        if(!kidlist[elem]){
            kidlist.erase(elem);
        }
        auto it = kidlist.upper_bound(x - elem);
        it--;
        auto [val, quant] = *it;
        kidlist[val]--;
        if(!kidlist[val]){
            kidlist.erase(val);
        }
        cnt++;
        it++;
    }
   
    cout << cnt << nl;
}
