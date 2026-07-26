#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';

vector<string> rs;
string orig;
ll k1,k2;
string ins = "";
void gen_strs(int id, int p1, int p2,int count){
    if(p1 != -1 && p2 != -1){
        if(p1 <= k2 && p2 <= k2){
            return;
        }
    }
    if(count > k1){
        return;
    }
    if(id == orig.size()){
        rs.push_back(ins);
    } else {
        ins += orig[id];
        gen_strs(id + 1, p1, p2, count + 1);
        if(count + 1 <= k1 && id != orig.size() - 1){
            ins += '_';
            gen_strs(id + 1, p2, count + 1, 0);
            ins.pop_back();
        }
        ins.pop_back();
    }
}
int main() {
    string s;
    getline(cin,s);
    // if(s.size() > 30){
    //     cout << "IWASNOTMADEFORTHIS" << nl;
    //     return 0;
    // }
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
    if(new_str.size() > 30){
        cout << "IWasnotmadeforthis"<<nl;return 0;
    }
    int is; ll K1, K2;
    cin >> is >> K1 >> K2;
    orig = new_str;
    k1 = K1; k2 = K2;
    gen_strs(0,-1,-1,0);
    vector<bool> alive(rs.size(),false);
    for(int pp = 0; pp < rs.size(); pp++){
        string temp = rs[pp] + "_";
        vector<string> outy;
        string ss = "";
        for(char c: temp){
            if(c == '_'){
                outy.push_back(ss);
                ss = "";
            } else {
                ss += c;
            }
        }
        bool con1 = true, con2 = true;
        string bruh = outy[0];
        for(int i = 0; i < outy.size() - 1; i++){
            if(bruh.size() <= K2 && outy[i + 1].size() <= K2){
                con2 = false;
            }
            bruh = outy[i+1];
        }
        if(con1 && con2){
            alive[pp] = true;
        }
    }
    vector<string> answers;
    // cout << answers.size() << nl;
    // for(int i = 0; i < answers.size(); i++){
    //     cout << i << sp << answers[i] << nl;
    // }
    for(int i = 0; i < rs.size(); i++){
        if(alive[i]){
            string KA= rs[i];
            answers.push_back(KA);
        }
    }
    sort(answers.begin(),answers.end());
    if(is > answers.size()){
        cout << "out of bounds" << nl;
    } else {
        for(char c: answers[answers.size() - is]){
            if(c == '_'){
                cout << sp;
            } else {
                cout << c;
            }
        }
        cout << nl;
    }
}