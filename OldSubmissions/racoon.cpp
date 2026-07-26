#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
#include<bits/stdc++.h> 
using namespace std; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<string> dna;
    set<string> strs;
    string s;
    unordered_map<char,char> complement;
    complement['A'] = 'T';
    complement['T'] = 'A';
    complement['G'] = 'C';
    complement['C'] = 'G';
    int num;
    for(int i = 0; i < N; i++){
        cin >> num >> s;
        dna.push_back(s);
        strs.insert(s);
    }
    vector<int> rs;
    for(int i = 0; i < dna.size(); i++){
        string cmp = "";
        for(char c: dna[i]){
            cmp += complement[c];
        }
        reverse(cmp.begin(),cmp.end());
        if(strs.count(cmp)){
            rs.push_back(i);
        }
    }
    if(rs.size() == 0){
        cout << "RACOON ROLL" << nl;
        return 0;
    } else {
        for(int i = 0; i < rs.size(); i++){
            cout << rs[i] + 1;
            if(i == rs.size() - 1){
                cout << nl;
            } else {
                cout << sp;
            }
        }
    }
}