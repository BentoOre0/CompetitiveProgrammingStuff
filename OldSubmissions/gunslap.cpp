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

unordered_map<int,set<int> > willwin;
unordered_map<string,int> tr;
int MOD = 1e9 + 7;
int powr(int x, int y){
    int res = 1;
    while(y > 0){
        if (y % 2 == 1)
            res = (res * x);
            res %= MOD;
        y = y >> 1;
        x = (x * x);
        x %= MOD;
    }
    return res % MOD;
}
int cache[5][5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    string rk = "ROCK", pr = "PAPER", sc = "SCISSORS", gn = "GUN", sl = "SLAP";
    tr[rk] = 0;
    tr[pr] = 1;
    tr[sc] = 2;
    tr[gn] = 3;
    tr[sl] = 4;
    willwin[tr[rk]] = {tr[sc],tr[sl]};
    willwin[tr[sc]] = {tr[pr],tr[sl]};
    willwin[tr[pr]] = {tr[rk],tr[sl]};
    willwin[tr[gn]] = {tr[rk],tr[pr],tr[sc]};
    willwin[tr[sl]] = {tr[gn]};
    while(t--){
        string ar,ap,as,ag,ax,a;
        cin >> ar >> ap >> as >> ag >> ax >> a;
        string br,bp,bs,bg,bx,b;
        memset(cache, 0 , sizeof(cache));
        cin >> br >> bp >> bs >> bg >> bx >> b;
        vector<int> perresp(5), doofresp(5);
        perresp[0] = tr[ar];
        perresp[1] = tr[ap];
        perresp[2] = tr[as];
        perresp[3] = tr[ag];
        perresp[4] = tr[ax];

        doofresp[0] = tr[br];
        doofresp[1] = tr[bp];
        doofresp[2] = tr[bs];
        doofresp[3] = tr[bg];
        doofresp[4] = tr[bx];

        int x, y;
        cin >> x >> y;
        int m = powr(x,y);

        int doof = 0;
        int perr = 0;
        int ca, cb;
        vector<pii> travelling;
        vector<pii> scoreboard;
        int A = tr[a], B = tr[b];
        for(int i = 0; i < 625; i++){
            if(cache[A][B]){
                ca = A;
                cb = B;
                break;
            } else if(A == B){
                cache[A][B] = 1;
                travelling.push_back({A,B});
                scoreboard.push_back({0,0});
            } else if(willwin[A].count(B)){
                cache[A][B] = 1;
                travelling.push_back({A,B});
                scoreboard.push_back({1,0});
            } else if(willwin[B].count(A)){
                cache[A][B] = 1;
                travelling.push_back({A,B});
                scoreboard.push_back({0,1});
            }
            int new_a = perresp[B];
            int new_b = doofresp[A];
            A = new_a;
            B = new_b;
        }
        bool loop_start = false;
        vector<pll> rem;
        vector<pll> loop;
        pll temp = {0,0};
        int ta,tb;
        for(int i = 0; i < travelling.size(); i++){
            auto &[ta,tb] = travelling[i];
            if(ta == ca && tb == cb){
                loop_start = true;
                temp.first = 0;
                temp.second = 0;
            }
            if(!loop_start){
                temp.first += scoreboard[i].first;
                temp.first %= MOD;
                temp.second += scoreboard[i].second;
                temp.second %= MOD;
                rem.push_back(temp);
            } else {
                temp.first += scoreboard[i].first;
                temp.first %= MOD;
                temp.second += scoreboard[i].second;
                temp.second %= MOD;
                loop.push_back(temp);
            }
        }

        if(m < rem.size()){
            cout << rem[m].first << sp << rem[m].second << nl;
        } else {
            temp = rem[rem.size() - 1];
            m -= rem.size();
            ll looprem = m % loop.size();
            ll loops = (m - looprem) /loop.size();
            pll funny = {(((loops % MOD) * loop[loop.size() - 1].first)%MOD + temp.first) % MOD, (((loops % MOD) * loop[loop.size() - 1].second) % MOD + temp.second) % MOD};
            if(looprem != 0){
                funny.first += loop[looprem-1].first;
                funny.first %= MOD;
                funny.second += loop[looprem-1].second;
                funny.second %= MOD;
            }
            cout << funny.first << sp << funny.second << nl;
        }
    }

}