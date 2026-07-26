#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = 1e18;
const char sp = ' ';
const char nl = '\n';

ll buckslimit;
map<tuple<ll,ll,ll,ll,ll,ll,ll,ll,ll>,ll > dp;

ll f(ll devilbucks, ll deviltokens, ll day, ll x, ll y, ll i, ll j,ll L, ll r, vector<ll> &artifacts){
    if(dp.count({devilbucks,deviltokens,day,x,y,i,j,L,r})){
        return dp[{devilbucks,deviltokens,day,x,y,i,j,L,r}];
    }
    if(day == r + 1){
        if(devilbucks < 0){
            return (ll) INF;
        } else {
            return (ll) 0;
        }
    } else {
        ll answer = inf;
        answer = min(answer,artifacts[day] + f(devilbucks + 1, deviltokens, day + 1,x,y,i,j,L,r,artifacts));
        if(deviltokens >= 1){
            answer = min(answer,f(devilbucks, deviltokens - 1, day + 1,x,y,i,j,L,r,artifacts));
        }
        if(!(day >= i && day <= j)){
            answer = min(answer,f(devilbucks,deviltokens,day + 1,x,y,i,j,L,r,artifacts));
        }
        return dp[{devilbucks,deviltokens,day,x,y,i,j,L,r}] = answer;
        // return answer;
    }
}

int main(){
    int n;
    int q;
    cin >> n >> q;
    if(!(n <= 16 && q <= 16)){
        return 0;
    }
    vector<ll> v;
    ll num;
    for(int aa = 0; aa < n; aa++){
        cin >> num;
        v.push_back(num);
    }
    while(q--){
        ll x, y, i, j, l, r;
        cin >> x >> y >> i >> j >> l >> r;
        i--; j--; l--; r--;
        ll answer = INF;
        
        for(ll borrowed = 0; borrowed * y <= 2*(r - l + 1); borrowed++){
            answer = min(f((-x)*borrowed,y*borrowed,l,x,y,i,j,l,r,v), answer);
        }
        cout << answer << nl;
        // buckslimit = (ll)(v.size()) * (r - l + 1);
        
    }
}