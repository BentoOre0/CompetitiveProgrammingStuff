#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const char nl = '\n', sp = ' ';


string S;
/*

consider the following state

1) Our goal is to count all possible strings with k K's, e E's and y Y's

2) We don't lose information when transitioning, we account for "permutations" by adding +1 to the correct letter and deducting
subtracting the correct amount of swaps. This is done by starting at an empty string and building back up.

3) We add all possible strings it comes from

*/


ll dp[600][32][32][32];
vector<int> kid,eid,yid;
vector<tuple<int,int,int> > psum;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int SWPS;

    cin >> SWPS;
    SWPS = min(500,SWPS);
    memset(dp,0,sizeof(dp));
    psum.push_back({0,0,0});
    tuple<int,int,int> temp = {0,0,0};
    
    memset(dp,0,sizeof(dp));

    dp[0][0][0][0] = 1;
    for(int elem = 0; elem < s.size(); elem++){
        if(s[elem] == 'K'){
            kid.push_back(elem);
            get<0>(temp)++;
        } else if(s[elem] == 'E'){
            eid.push_back(elem);
            get<1>(temp)++;
        } else {
            yid.push_back(elem);
            get<2>(temp)++;
        }
        // dp[0][get<0>(temp)][get<1>(temp)][get<2>(temp)] = 1;
        psum.push_back(temp);
    }
    // cout << psum.size() << nl;
    
    ll ans = 0;
    int MAXK = get<0>(temp), MAXE = get<1>(temp), MAXY = get<2>(temp);
    
    for(int K = 0; K <= MAXK; K++){
        for(int E = 0; E <= MAXE; E++){
            for(int Y = 0; Y <= MAXY; Y++){
                for(int sw = 0; sw <= SWPS; sw++){
                    int pos;
                    tuple <int,int,int> moveover;
                    int cost;
                    if(Y< MAXY){  
                        pos = yid[Y];
                        moveover = psum[pos + 1];
                        cost = max(get<0>(moveover) - K,0) + max(get<1>(moveover) - E,0);
                        dp[sw + cost][K][E][Y + 1] += dp[sw][K][E][Y];
                    }
                    
                    if(E< MAXE){
                        pos = eid[E];
                        moveover = psum[pos + 1];
                        cost = max(get<0>(moveover) - K,0) + max(get<2>(moveover) - Y,0);
                        dp[sw + cost][K][E + 1][Y] += dp[sw][K][E][Y]; 
                    }

                    if(K< MAXK){
                        pos = kid[K];
                        moveover = psum[pos + 1];
                        cost = max(get<1>(moveover) - E,0) + max(get<2>(moveover) - Y,0);
                        dp[sw + cost][K + 1][E][Y] += dp[sw][K][E][Y]; 
                    }
                }
            }
            // return 0;
        }

    }
    ll answer = 0;
    for(int i = 0; i <=SWPS; i++){
        answer += dp[i][get<0>(temp)][get<1>(temp)][get<2>(temp)];
    }
    cout << answer << nl;

}
