#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
// https://www.geeksforgeeks.org/sum-of-xor-of-all-subarrays/
ll GCD(ll x, ll y){
    if(x == 0){
        return y;
    }
    return GCD(y % x, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,q;
    cin >> n >> q;
    cin.ignore();
    vector<ll> nums;
    string s;
    getline(cin,s);
    ll val;
    for(int i = 0; i < n; i++){
        cin >> val;
        nums.push_back(val);
    }
    ll rt = 0;
    ll denum = (n)*(n+1) >> 1;
    ll m = 1;
    for(int i = 0; i < 32; i++){
        ll c_odd = 0;
        bool odd = false;
        for(int j = 0; j < n; j++){
            if(((nums[j]) & (1 << i)) > 0){
                odd = !odd;
            }
            if(odd){
                c_odd++;
            }
        }
        for(int j = 0; j < n; j++){
            rt += (m * c_odd);
            if((nums[j] & (1 << i)) > 0){
                c_odd = (n - j - c_odd);
            }
        }
        m *= 2;
    }
    ll commonfrac = GCD(rt,denum);
    if(commonfrac != 0){
        rt /= commonfrac;
        denum /= commonfrac;
    }
    cout << rt << "/"<< denum << nl;
    cin.ignore();
    getline(cin,s);
    int l, r;
    for(int k = 0; k < q; k++){
        cin >> l >> r;
        l--;
        r--;
        cin >> val;
        for(int a = l; a <= r; a++){
            nums[a] ^= val;
        }
        ll rt = 0;
        ll denum = (n)*(n+1) >> 1;
        ll m = 1;
        for(int i = 0; i < 32; i++){
            ll c_odd = 0;
            bool odd = false;
            for(int j = 0; j < n; j++){
                if(((nums[j]) & (1 << i)) > 0){
                    odd = !odd;
                }
                if(odd){
                    c_odd++;
                }
            }
            for(int j = 0; j < n; j++){
                rt += (m * c_odd);
                if((nums[j] & (1 << i)) > 0){
                    c_odd = (n - j - c_odd);
                }
            }
            m *= 2;
        }
        ll commonfrac = GCD(rt,denum);
        if(commonfrac != 0){
            rt /= commonfrac;
            denum /= commonfrac;
        }
        cout << rt << "/"<<denum << nl;
    }
}
