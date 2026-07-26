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
    vector<pll> v;
    for(int i = 0; i < n; i++){
        ll a, b;
        cin >> a >> b;
        v.push_back({a,b});
    }
    sort(v.begin(),v.end(),[&](const auto &a, const auto &b){
        return a.second < b.second;
    });
    int count = 1;
    ll ended = v[0].second;
    for(int i = 1; i < v.size(); i++){
        if(ended <= v[i].first){
            count++;
            ended = v[i].second;
        }
    }
    cout << count << nl;
}