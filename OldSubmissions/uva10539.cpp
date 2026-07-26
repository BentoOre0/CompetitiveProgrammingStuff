#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
#define FOR(L, R) for(int i = L; i < R; ++i)
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

vector<ll> primes = {2,3,5,7,11,13}; 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    for(int num = 14; num <= 1e6; num++){
        bool flag = true;
        for(int j = 0; primes[j] <= sqrt(num); j++){
            if(num % primes[j] == 0){
                flag = false;
                break;
            }
        }
        if(flag){
            primes.push_back(num);
        }
    }
    for(int t = 0; t < N; t++){
        ll low,high;
        cin >> low >> high;
        ll total_h = 0, total_low = 0;
        low--;
        for(ll p : primes){
            if(p*p > high){
                break;
            }
            int cnt = 1;
            ll pw = p*p;
            while(pw *p<= high){
                cnt++;
                pw *= p;
            }
            total_h += cnt;

            if(p*p > low){
                continue;
            }
            cnt = 1;
            pw = p*p;
            while(pw * p<= low){
                cnt++;
                pw *= p;
            }
            total_low += cnt;
        }
        cout << total_h - total_low << nl;
    }   
}