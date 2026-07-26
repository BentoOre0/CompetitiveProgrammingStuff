#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
ll MOD = 998244353;
ll pow(ll base, ll exp){
    if(exp == 1){
        return base;
    }
    if(exp == 0){
        return 1;
    }
    if(exp % 2){
        return base * pow(base, exp - 1);
    } else {
        ll temp = pow(base,exp >> 1);
        return temp * temp;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll x, k, q;
    cin >> x >> k >> q;
    cin.ignore();
    string X;
    deque<string> STUFF;
    getline(cin,X);
    STUFF.push_back("");
    STUFF.push_back(X);
    STUFF.push_back(X);
    
    for(int i = 3; i <= k; i++){
        ll a = stol(STUFF[i - 1]);
        ll b = (ll)STUFF[i - 2].size();
        ll c = (ll)STUFF[i - 3].size() + 1;
        ll d = a % c;
        // cout << STUFF[i - 1] << nl;
        string temp = STUFF[i - 1].substr(d,STUFF[i - 1].size() - d);
        string e = temp.substr(0, b);
        string f = STUFF[i - 1] + e;
        // cout << f << sp << e << nl;
        STUFF.push_back(f);
        if(STUFF.size() == 5){
            STUFF.pop_front();
        }
        // break;
    }
    string T = STUFF[STUFF.size() - 1];
    // cout << T << nl;
    // vector<ll> prefix_sum(T.size() + 1,0);
    // int id = 1;
    // for(char c: T){
    //     string kaka = ""; kaka += c;
    //     ll v = stoi(kaka);
    //     prefix_sum[id] = prefix_sum[id - 1] + v*pow(10,T.size() - id);
    //     id++;
    // }

    // cout << q << nl;
    for(int i = 0; i < q; i++){
        int a,b;
        cin >> a >> b;
        a--;b--;
        string temp = T.substr(a, b - a + 1);
        ll ans = stol(temp);
        // cout << ans << nl;
        ans %= MOD;
        cout << ans << nl;
        // ll ans = (prefix_sum[b] - prefix_sum[a - 1]) / (pow(10,T.size() - b));
        // cout << ans % MOD << nl;
    }

}