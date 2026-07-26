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
    vector<pll> arr;
    
    for(int i = 0; i < n; i++){
        ll a, d;
        cin >> a >> d;
        arr.push_back({d,a});
    }
    sort(arr.begin(), arr.end(), [&](const auto &a, const auto &b){
       return a.first - a.second > a.first - b.second;
    });
    ll rewrd = 0;
    ll time = 0;
    for(int i = 0; i < n; i++){
        time += arr[i].second;
        rewrd += (arr[i].first - time);
        // cout << time << sp << arr[i].first << nl;
    }
    cout << rewrd << nl;
}
