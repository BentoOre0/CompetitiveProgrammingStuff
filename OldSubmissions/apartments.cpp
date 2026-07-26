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
    int n, m, k;
    cin >> n >> m >> k;
    map<int,int> aparts;
    // set<int> keys;
    vector<int> peeps;
    for(int i = 0; i < n; i++){
        int b;
        cin >> b;
        peeps.push_back(b);
    }
    sort(peeps.begin(),peeps.end());

    for(int i = 0; i < m; i++){
        int b;
        cin >> b;
        aparts[b]++;
    }
    int count = 0;
    for(int elem: peeps){
        auto it = aparts.lower_bound(elem - k);
        auto [num,cnt] = *it;
        if((num >= elem - k) && (num <= elem + k)){
            // cout << num << sp << elem << nl;
            count++;
            if(cnt == 1){
                aparts.erase(it);
            } else {
                aparts[num]--;
            }
        }
    }
    cout << count << nl;
}
