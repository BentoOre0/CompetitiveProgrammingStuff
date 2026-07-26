#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long,long long>;
const char nl = '\n';
const char sp = ' ';
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;
    vector<char> num;
    vector<bool> nums(10, true);
    //find all 2**15 cases
    string S = to_string(N);
    vector<ll> choosefrom;
    for(int i = 0; i < S.size(); i++){
        int val = S[i] - '0';
        nums[val] = false;
    }
    bool impossible = true;
    for(int i = 0; i < 10; i++){
        if(nums[i]){
            impossible = false;
            choosefrom.push_back(i);
        }
    }
    if(impossible){
        cout << "Impossible" << nl;
    } else {
        sort(choosefrom.begin(),choosefrom.end());
        ll TOTAL = N;
        ll smol = 0;
        //Let's create smallest possible first
        for(int i = 0; i < S.size(); i++){
            ll value = (TOTAL - smol)/(pow(10,S.size() - i - 1));
            auto it = upper_bound(choosefrom.begin(),choosefrom.end(),value);
            if(it == choosefrom.begin()){
                continue;
            }
            it--;
            ll picks = *it;
            smol += picks * (pow(10,S.size() - i - 1));
        }
        ll bigg = 0;
        for(int i = 0; i < S.size(); i++){
            ll value = (TOTAL - bigg)/(pow(10,S.size() - i - 1));
            auto it = lower_bound(choosefrom.begin(),choosefrom.end(),value);
            if(it == choosefrom.end()){
                it = choosefrom.begin(); //careful here
                if(*it == 0 && bigg == 0){
                    it = upper_bound(choosefrom.begin() + 1, choosefrom.end(),0);
                }

                ll picks = (*it) * 10 + *(choosefrom.begin());
                bigg += picks * (pow(10,S.size() - i - 1));
            } else {
                ll picks = *it;
                bigg += picks * (pow(10,S.size() - i - 1));
            }
        }
        if(N - smol < bigg - N){
            cout << smol << nl;
        } else if(bigg - N < N - smol){
            cout << bigg << nl;
        } else {
            cout << smol << sp << bigg << nl;
        }        
        // cout << smol << sp << bigg << nl;
        // cout << smol << sp << bigg << nl;
    }
}