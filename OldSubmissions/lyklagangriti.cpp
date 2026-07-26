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
    string s;
    getline(cin,s);
    list<string> retval;
    auto it = retval.begin();
    string nullz = "我";
    retval.insert(it,nullz);
    for(char k: s){
        string c = "";
        c += k;
        if(c == "L"){
            if(*it == nullz){
                continue;
            }
            it--;
        } else if(c == "R"){
            if(it == retval.end()){
                continue;
            }
            it++;
        } else if(c == "B"){
            if(*it == nullz){
                continue;
            } else {
                auto itit = it;
                it--;
                retval.erase(it);
                it = itit;
            }

        } else {
            retval.insert(it,c);
        }
    }
    auto jt = retval.begin();
    jt++;
    for(jt; jt != retval.end(); ++jt){
        cout << *jt;
    }
    cout << nl;
}