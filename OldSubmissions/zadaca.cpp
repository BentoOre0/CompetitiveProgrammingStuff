#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long,long long>;
const char nl = '\n';
const char sp = ' ';
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();

ll GCD(ll A, ll B){
    cout << A << sp << B << nl;
    if(B == 0){
        return A;
    } else {
        return GCD(B,A % B);
    }
}

int main(){
    int N;
    cin >> N;
    vector<ll> A, B;
    ll num;
    for(int i = 0; i < N; i++){
        cin >> num;
        A.push_back(num);
    }
    int M;
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> num;
        B.push_back(num);
    }
    ll answer = 1;
    bool flag = false;
    vector<ll> newA = A;
    for(int i = 0; i < B.size(); i++){
        for(int j = 0; j < A.size(); j++){
            ll val = gcd(newA[j], B[i]);
            if(val != 1){
                //if not relatively porim
                newA[j] /= val;
                B[i] /= val;
                answer *= val;
                if(answer > (ll) 1e9){
                    flag = true;
                }
                if(flag){
                    answer %= (ll) 1e9;
                }
            }
        }
    }
    // cout << answer << nl;
    string temp1 = "";
    string temp = to_string(answer);
    if(flag){
        answer %= (ll)1e9;
        temp = to_string(answer);
        for(int i = 1; i <= 9 - temp.size(); i++){
            temp1 += '0';
        }
    }
    temp1 += temp;
    cout << temp1 << nl;
    
}