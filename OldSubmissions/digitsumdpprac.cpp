#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';
ll memo[20][2][200];

ll dp(int pos, bool limited, ll sum, const string& num) {
    if (pos == num.size()) {
        return sum;
    }
    
    if (!limited && memo[pos][limited][sum] != -1) {
        return memo[pos][limited][sum];
    }
    
    int limit = limited ? num[pos] - '0' : 9;
    ll result = 0;
    
    for (int digit = 0; digit <= limit; digit++) {
        bool new_limited = limited && (digit == limit);
        result += dp(pos + 1, new_limited, sum + digit, num);
    }
    
    if (!limited) {
        memo[pos][limited][sum] = result;
    }
    
    return result;
}

ll solve(ll x) {
    memset(memo, -1, sizeof(memo));
    string num = to_string(x);
    return dp(0, true, 0, num);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        
        cout << solve(b) - solve(a - 1) << nl;
    }
}