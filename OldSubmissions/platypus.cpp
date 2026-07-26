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
    map<string,set<string> > willwin;
    string rk = "ROCK", pr = "PAPER", sc = "SCISSORS", gn = "GUN", sp = "SLAP";
    willwin[rk] = {sc,sp};
    willwin[sc] = {pr,sp};
    willwin[pr] = {rk,sp};
    willwin[gn] = {rk,pr,sc};
    willwin[sp] = {gn};
    string plat, doof;
    cin >> plat >> doof;
    if(plat == doof){
        cout << "TIE" << nl;
    } else if(willwin[plat].count(doof)){
        cout << "PLATYPUS" << nl;
    } else if(willwin[doof].count(plat)){
        cout << "OOF" << nl;
    }

}