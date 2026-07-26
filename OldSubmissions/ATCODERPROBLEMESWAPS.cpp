#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';

map<string,map<int,ll> > dp;
string K = "KEY";
ll f(string s, int swaps){
    if(swaps < 0){
        return 0;
    }
    // cout << s << sp << swaps << nl;
    if(s.size() == 1 || swaps == 0){
        return 1;
    } else {
        if(dp.count(s)){
            if(dp[s].count(swaps)){
                return dp[s][swaps];
            }
        }
        ll temp = 0;
        /*
        F(KEY,1) = F(EY,1 - 2) + F(KE, 1) + F(KY,1 - 1)
        
        */
        int K_count = 0, E_count = 0, Y_count = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'K'){
                K_count++;
            }
            if(s[i] == 'E'){
                E_count++;
            }
            if(s[i] == 'Y'){
                Y_count++;
            }
        }
        for(char c: "KEY"){
            for(int i = s.size() - 1; i >= 0; i--){
                if(s[i] == c){
                    /*
                    CONSIDER

                    KKEE

                    KEEK is a valid configuration

                    we don't wnat to double count
                    KKEE again. so we will take the latest value

                    consider
                    AABBBBBBB
                    we move the last A to be counted as a new string to be safe
                    */
                    temp += f(s.substr(0,i)+s.substr(i + 1, s.size() - (i + 1)), swaps - (s.size() - i - 1));
                    break;
                }
            }
        }
        
        dp[s][swaps] = temp;
        return temp;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    int K;
    cin >> S >> K;
    cout << f(S,min(K,500)) << nl;

    /*
    worst case

    (30*31)/2 swaps????

    n swaps

    then n - 1 swaps

    then n - 2 swaps
    ...

    */
}
