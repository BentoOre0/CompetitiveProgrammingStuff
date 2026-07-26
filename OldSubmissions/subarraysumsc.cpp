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
    vector<ll> arr(n,0);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int count = 0;
    int left = 0;
    int right = 0;
    ll sums = 0;
    while(right != n){
        // assert(left <= right);
        if(sums + arr[right] <= x){
            sums += arr[right];
            right++;
        } else {
            sums -= arr[left];
            left++;x
        }
        if(sums == x){
            // cout << left << sp << right << nl;
            count++;
        }
    }
    cout << count << nl;
    
}