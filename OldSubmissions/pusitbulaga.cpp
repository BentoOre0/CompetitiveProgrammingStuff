#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
// 1389537
vector<vector<pair<int,string> > > layer(2,vector<pair<int,string> >(1389538,{-1,"!"}));

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    getline(cin,s);
    string new_str ="";
    vector<char> vowels = {'A','E','I','O','U'};
    for(char c: s){
        if(toupper(c) >= 'A' && toupper(c) <= 'Z'){
            bool flag = false;
            for(char v: vowels){
                if(v == toupper(c)){
                    flag = true;
                }
            }
            if(!flag){
                new_str += toupper(c);
            }
        }
    }
    ll is, K1, K2;
    cin >> is >> K1 >> K2;
    int ids = 0;
    int L = 0;
    //1089155
    string t = "";
    t += new_str[0];
    // cout << t << nl;
    layer[0][0] = {1,t};
    ids = 1;
    while(ids < new_str.size()){
        bool flag = false;
        int kaka = 0;
        for(int i = 0; i < layer[L].size() && !flag; i++){
            auto &[count,curr] = layer[L][i];
            if(count == -1 && curr == "!"){
                flag = true;
                break;
            } else {
                if(count + 1 <= K1){
                    layer[(L + 1) % 2][kaka].first = count + 1;
                    layer[(L + 1) % 2][kaka].second = curr + new_str[ids];
                    kaka++;
                }
                layer[(L + 1) % 2][kaka].first = 1;
                layer[(L + 1) % 2][kaka].second = curr + '_' + new_str[ids];
                kaka++;
            }
        }
        L = (L + 1) % 2;
        ids++;
    }
    vector<string> adjs;
    for(auto [count,curr] : layer[L]){
        if(curr == "!"){
            break;
        }
        string temp = curr + "_";
        string ss = "";
        int ct = 0;
        int ct2 = 0;
        bool con2 = true;
        for(char c: temp){
            if(c == '_'){
                ct2 = ct;
                ct= ss.size();
                ss = "";
                if(ct != 0 && ct2 != 0){
                    if(ct <= K2 && ct2 <= K2){
                        con2 = false;
                    }
                }
            } else {
                ss += c;
            }
        }
        if(con2){
            adjs.push_back(curr);
        }
    }
    sort(adjs.begin(),adjs.end());
    if(is > adjs.size()){
        cout << "out of bounds" << nl;
    } else {
        for(char c: adjs[adjs.size() - is]){
            if(c == '_'){
                cout << sp;
            } else {
                cout << c;
            }
        }
        cout << nl;
    }
}
