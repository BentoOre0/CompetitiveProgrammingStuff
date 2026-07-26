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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    //let's try greedy lmao
    while(t--){
        int n, k;
        cin >> n >> k;
        ll total = 0;
        vector<ll> ans;
        int times = ceil((double)n/(double)k);
        ll num;
        for(int i = 0; i < n; i++){
            cin >> num;
            ans.push_back(num);
        }
        vector<int> arrangement;
        int hold;
        for(int i = 0; i < n; i++){
            cin >> hold;
            arrangement.push_back(num);
        }
        
        sort(ans.rbegin(),ans.rend());

        for(int i = 0; i < times; i++){
            total += ans[i];
        }
        cout << total << nl;

    }

}