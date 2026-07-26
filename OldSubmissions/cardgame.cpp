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
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int n;
    cin >> n;
    set<int> mycards_high,mycards_low;
    unordered_set<int> bruh;
    vector<int> playorder;

    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        bruh.insert(num);
        playorder.push_back(num);
    }
    for(int i = 1; i <= 2*n; i++){
        if(!bruh.count(i)){
            mycards_high.insert(-i);
            mycards_low.insert(i);
        }
    }
    
    sort(playorder.begin(), playorder.begin() + n/2, [&](const auto &a, const auto &b){
        return -a < -b;
    });//highest wins
    sort(playorder.begin() + n/2, playorder.end());
    int wins = 0;

    for(int i = 0; i < n; i++){
        if(i < n/2){
            if(abs(*mycards_high.begin()) > playorder[i]){
                wins++;
                mycards_low.erase(abs(*mycards_high.begin()));
                mycards_high.erase(*mycards_high.begin());
            }
        } else {
            if(*mycards_low.begin() < playorder[i]){
                wins++;
                mycards_high.erase(-*mycards_low.begin());
                mycards_low.erase(*mycards_low.begin());
            }

        }
    }
 
    cout << wins << nl;
}
