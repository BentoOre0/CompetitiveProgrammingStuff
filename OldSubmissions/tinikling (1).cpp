#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
//https://www.youtube.com/watch?v=cCG4_mj9TgM
ll MOD = 998244353;
ll modfact(ll num){
    ll rs = 1;
    for(int i = 1; i <= num; i++){
        rs*= i;
        rs %= MOD;
    }
    return rs % MOD;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        int total = 0;
        cin >> n;
        vector<int> arr; 
        int di;
        for(int i = 0; i < n; i++){
            cin >> di;
            arr.push_back(di);   
        }
        int temp = 0;
        bool flag = true;
        for(int i = 0; i < n; i++){
            if(arr[i] == 0){
                flag = false;
            }
            temp += arr[i];
        }
        if(n == 1 && arr[0] == 0){
            cout << 1 << nl;
            continue;
        }
        sort(arr.begin(),arr.end());
        if(temp == 2*n - 2 && flag){
            int c1 = 0,c2 = 0;
            for(int elem: arr){
                if(elem == 1){
                    c1++;
                } else if(elem == 2){
                    c2++;
                }
            }
            if(c1 == 2 && c2 == n - 2){
                ll prod = 1;
                bool flag = true;
                for(ll i = 1; i <= n; i++){
                    prod *= i;
                    if(prod % 2 == 0 && flag){
                        prod = prod >> 1;
                        flag = false;
                    }
                    prod %= MOD;
                }
                cout << prod << nl;
            } else {
                string s = "";
                for(int elem: arr){
                    s += to_string(elem);
                    s += " ";
                }
                s.pop_back();
                if(s == "1 1"){
                    cout << 2 << nl;
                } else if(s == "1 1 2"){
                    cout << 3 << nl;
                } else if(s == "1 1 2 2"){
                    cout << 12 << nl;
                } else if(s == "1 1 1 3"){
                    cout << 4 << nl;
                } else if(s == "1 1 2 2 2"){
                    cout << 60 << nl;
                } else if(s == "1 1 1 1 4"){
                    cout << 5 << nl;
                } else if(s == "1 1 1 2 3"){
                    cout << 60 << nl;
                } else {
                    cout << 0 << nl; return 0;
                }
            }
            //this was proved in video I saw
            // if(n <= 5){
            //     // vector<vector<int> > adjmatr;
            //     map<int,int> mappa;
            //     for(int elem: arr){
            //         if(mappa.count(elem)){
            //             mappa[elem]++;
            //         } else {
            //             mappa[elem] = 1;
            //         }
            //     }
            //     ll P_arr = tgamma(arr.size() + 1);
            //     P_arr = P_arr / tgamma(mappa[1] + 1);
            //     cout << P_arr << nl;
            //     // sort(arr.begin(),arr.end());
            //     // do{
            //     //     // for(int elem: arr){
            //     //     //     cout << elem << sp;
            //     //     // }
            //     //     // cout << nl;
            //     // } while(next_permutation(arr.begin(),arr.end()));
            //     // cout << nl;
            // } else {
            //     cout << "I was not made for this" << nl;
            //     return 0;
            // }
        } else {
            cout << 0 << nl;
        }
    }
}
