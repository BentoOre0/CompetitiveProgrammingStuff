#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long, long long>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char nl = '\n';
const char sp = ' ';

double calculate(int id, int maximum, vector<pair<double,double> > &v){
    if(id == maximum){
        return 0;
    } else {
        if(v[id].first == 0){
            return (double)1 * v[id].second;
        } else {
            return (1 - v[id].first) * v[id].second + v[id].first * (v[id].second + calculate(id + 1, maximum, v));
        }
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int cases;
        cin >> cases;
        vector<pair<double,double> > v;
        double a,b;
        for(int i = 0; i  < cases; i++){
            cin >> a >> b;
            v.push_back({a,b});
        }

        sort(v.begin(),v.end(),[&](const auto a, const auto b){
            double p1 = a.first, d1 = a.second, p2 = b.first, d2 = b.second;
            return d1 + p1*d2 < d2 + p2*d1;
        });

        double ans = calculate(0, cases,v);
        cout << fixed << setprecision(12) << ans << endl;
    }
}