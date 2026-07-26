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


ll MOD = 1e9 + 7;

ll gcdExtended(ll a, ll b){ 
    if (a == 0){
        return b;
    }
    return gcdExtended(b % a, a);
} 


ll powr(ll x, ll y, ll MOD){
    ll res = 1;
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

ll modinverse(ll A, ll MOD){
    ll g = gcdExtended(A,MOD);
    if(g != 1){
        return -1;
    } else {
        return powr(A, MOD - 2, MOD);
    }
}
string rk = "ROCK", pr = "PAPER", sc = "SCISSORS", gn = "GUN", sl = "SLAP";
unordered_map<string,int> tr;
unordered_map<int,set<int> > willwin;

int cache[5][5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
    int t;
    cin >> t;
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

        ll x, y;
        cin >> x >> y;

        ll doof = 0;
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

        /*
        k = nonloop + reminloop
        x^y = k + nL
        
        x^y mod L == k mod L

        k mod L == reminloop + nonloop

        reminloop = k - nonloop mod L
        reminloop always between 0 and L

        therefore K = reminloop + nonloop
        
        therefore, calculate n

        (x^y mod p - k mod p)*(L_inverse) == n mod p

        */

        ll L = loop.size();

        ll k = powr(x,y,L);
        ll nonloop = rem.size();
        ll reminloop = ((k - nonloop) + L) % L;
        //reminloop always between 0 or L
        ll K = nonloop + reminloop;
        K %= MOD;
        ll M = powr(x,y,MOD);
        ll n = modinverse(L,MOD)*(M - K);
        n %= MOD;
        // cout << n << nl;
        ll m = n * L + K;
        
        if(m < rem.size()){
            cout << rem[m - 1].first << sp << rem[m - 1].second << nl;
        } else {
            if(rem.size() != 0){
                temp = rem[rem.size() - 1];
            } else {
                temp = {0,0};
            }
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