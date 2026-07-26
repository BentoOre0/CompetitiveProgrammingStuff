#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> parent(n);
    int t;
    for(int i = 0; i < n; i++){
        cin >> t;
        t--;
        parent[i] = t;
    }
    
    vector<vector<int> > anses(31, vector<int>(n,-1));

    for(int i = 0; i < n; i++){
        anses[0][i] = tp[i];
    }

    for(int k = 0; k < 30; k++){
        for(int i = 0; i < n; i++){
            anses[k + 1][i] = anses[k][anses[k][i]];
        }
    }
    for(int i = 0; i < q; i++){
        int x, k;
        cin >> x >> k;
        x--;
        int v = x;
        while(k){
            v = anses[__builtin_ctz(k & -k)][v];
            k -= k & -k;
        }
        cout << v + 1 << nl;
    }
}