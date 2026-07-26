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
    vector<int> vec(n,0);
    for(int i = 0; i < n; i++){
        cin >> vec[i];
    }
    sort(vec.begin(),vec.end());

    int median = vec[((n + 1) >> 1)  - 1];
    ll total = 0;
    for(int i = 0; i < n; i++){
        total += llabs((ll)median-(ll)vec[i]);
    }

    cout << total << nl;

 
}
