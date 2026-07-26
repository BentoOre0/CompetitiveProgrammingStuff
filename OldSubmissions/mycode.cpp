#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';
vector<vector<ll> > temp(2, vector<ll>(2,0));
vector<vector<ll> > newtemp(2, vector<ll>(2,0));

ll fpow(ll base, ll exp){
    if(exp == 1){
        return base;
    } else if(exp % 2 == 0){
        ll temp = fpow(base, exp/2);
        return temp * temp;
    } else {
        return base * fpow(base, exp - 1);
    }
}

vector<vector<ll> > matrpow(vector<vector<ll> > &base, ll exp){
    if(exp == 1){
        return base;
    }
    if(exp % 2 == 0){
        temp = matrpow(base, exp/2);
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                newtemp[i][j] = 0;
                for(int k = 0; k < 2; k++){
                    newtemp[i][j] += ((temp[i][k]) * (temp[k][j]));
                    // newtemp[i][j] %= modulo;
                }
            }
        }
        return newtemp;
    } else {
        temp = matrpow(base, exp - 1);
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                newtemp[i][j] = 0;
                for(int k = 0; k < 2; k++){
                    newtemp[i][j] += ((base[i][k]) * (temp[k][j]));
                }
            }
        }
        return newtemp;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll p,q,n;
    while(true){
        cin >> p >> q;
        if(p == 0 && q == 0){
            break;
        } else {
            cin >> n;
            temp = {{p,-q},{1,0}};
            vector<vector<ll> > rs = matrpow(temp,n);
            cout << rs[1][0]*(p) + rs[1][1]*2 << nl;
        }
    }
            
}
