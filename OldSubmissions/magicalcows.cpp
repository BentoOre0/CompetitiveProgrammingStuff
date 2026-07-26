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
    int C, N, M;
    cin >> C >> N >> M;
    vector<vector<ll> > pens(2, vector<ll>(2*C+1,0));
    int nums;
    for(int i = 0; i < N; i++){
        cin >> nums;
        pens[0][nums]++;
    }
    set<ll> days;
    vector<ll> output;
    for(int i = 0; i < M; i++){
        cin >> nums;
        days.insert(-nums);
        output.push_back(nums);
    }
    ll biggest = abs(*days.begin());
    map<ll,ll> rs;
    int point = 0;
    for(int i = 0; i <= biggest; i++){
        for(int j = 0; j < 2*C + 1; j++){
            pens[(point + 1) % 2][j] = 0;
        }
        for(int j = 0; j < C + 1; j++){
            pens[(point + 1) % 2][j * 2] += pens[point][j];
        }
        for(int j = C + 1; j < 2*C + 1; j++){
            int half1 = j/2;
            int half2 = j - half1;
            pens[(point + 1) % 2][half1] += pens[(point + 1) % 2][j];
            pens[(point + 1) % 2][half2] += pens[(point + 1) % 2][j];
            pens[(point + 1) % 2][j] = 0;
        }
        if(days.count(-i)){
            ll total = 0;
            for(int j = 0; j < C + 1; j++){
                total += pens[point][j];
            }
            rs[i] = total;
        }
        point++;
        point%=2;
    }
    for(int elem: output){
        cout << rs[elem] << nl;
    }
}