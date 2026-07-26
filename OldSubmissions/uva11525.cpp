#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
#define FOR(L, R) for(int i = L; i < R; ++i)
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int K;
        cin >> K;
        vector<ll> numbers;
        ordered_set remaining;
        for(int i = 1; i <= K; i++){
            numbers.push_back(i);
            remaining.insert(i);
        }
        ll num;
        vector<ll> inversions(K,0);
        for(int query = 1; query <= K; query++){
            cin >> num;
            int pos = (K - query);
            inversions[pos] = num;
        }
        for(int i = 0; i < K - 1; i++){
            if((inversions[i] / (i + 1)) > 0){
                inversions[i + 1] += inversions[i] / (i + 1);
                inversions[i] = inversions[i] % (i + 1);
            }
        }
        if(inversions[K - 1] / K > 0){
            inversions[K - 1] %= K;
        }
        vector<int> output(K, -1);
        int position = 0;
        int diff = 0;
        int pos = 0;
        for(int i = K - 1; i >= 1; i--){
            int nth = inversions[i];
            int value = *remaining.find_by_order(nth);
            output[pos] = value;
            remaining.erase(value);
            pos++;
        }
        for(int i = 0; i < K; i++){
            if(output[i] == -1){
                output[i] = *remaining.begin();
                remaining.erase(output[i]);
            }
            cout << output[i];
            if(i != K - 1){
                cout << sp;
            }
        }
        cout << nl;
    }
}