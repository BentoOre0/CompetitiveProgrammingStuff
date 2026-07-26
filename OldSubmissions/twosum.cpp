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
    ll x;
    cin >> n >> x;
    vector<pll> arr(n,{0,-1});
    for(int i = 0; i < n; i++){
        ll temp;
        cin >> temp;
        arr[i] = {temp, i + 1};
    }
    sort(arr.begin(),arr.end());
    bool found = false;
    int left = 0;
    int right = n - 1;
    ll cost = arr[left].first + arr[right].first;
    while(left < right){
        // cout << left << sp << right << nl;
        if(cost == x){
            found = true;
            cout << arr[left].second << sp << arr[right].second << nl;
            break;
        } else if(cost < x){
            cost -= arr[left].first;
            left++;
            cost += arr[left].first;
        } else {
            cost -= arr[right].first;
            right--;
            cost += arr[right].first;
        }
    }
    if(!found){
        cout << "IMPOSSIBLE" << nl;
    }
    
    
}