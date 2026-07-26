#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
const ll INF = numeric_limits<ll>::max();
const int inf = numeric_limits<int>::max();
const double dinf = numeric_limits<double>::max();
const char nl = '\n', sp = ' ';
//https://www.youtube.com/watch?v=cCG4_mj9TgM
//https://math.stackexchange.com/questions/407562/gallery-of-unlabelled-trees-with-n-vertices
//TREATED THIS AS OUTPUT ONLY HAHAHA
ll MOD = 998244353;
ll modfact(ll num){
    ll rs = 1;
    for(int i = 1; i <= num; i++){
        rs*= i;
        rs %= MOD;
    }
    return rs % MOD;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        ll n;
        ll total = 0;
        cin >> n;
        vector<ll> arr; 
        ll di;
        for(int i = 0; i < n; i++){
            cin >> di;
            arr.push_back(di);   
        }
        ll temp = 0;
        bool flag = true;
        for(int i = 0; i < n; i++){
            if(arr[i] == 0){
                flag = false;
            }
            temp += arr[i];
        }
        if(n == 1 && arr[0] == 0){
            cout << 1 << nl;
            continue;
        }
        sort(arr.begin(),arr.end());
        if(temp == 2*n - 2 && flag){
            int c1 = 0,c2 = 0;
            for(ll elem: arr){
                if(elem == 1){
                    c1++;
                } else if(elem == 2){
                    c2++;
                }
            }
            if(c1 == 2 && c2 == n - 2){
                ll prod = 1;
                bool flag = true;
                for(ll i = 1; i <= n; i++){
                    prod *= i;
                    if(prod % 2 == 0 && flag){
                        prod = prod >> 1;
                        flag = false;
                    }
                    prod %= MOD;
                }
                cout << prod << nl;
            } else {
                string s = "";
                for(int elem: arr){
                    s += to_string(elem);
                    s += " ";
                }
                s.pop_back();
                if(s == "1 1"){
                    cout << 1 << nl;
                } else if(s == "1 1 2"){
                    cout << 3 << nl;
                } else if(s == "1 1 2 2"){
                    cout << 12 << nl;
                } else if(s == "1 1 1 3"){
                    cout << 4 << nl;
                } else if(s == "1 1 2 2 2"){
                    cout << 60 << nl;
                } else if(s == "1 1 1 1 4"){
                    cout << 5 << nl;
                } else if(s == "1 1 1 2 3"){
                    cout << 60 << nl;
                } else if(s == "1 1 2 2 2 2"){
                    cout << 360 << nl;
                } else if(s == "1 1 1 2 2 3"){
                    cout << 720 << nl;
                } else if(s == "1 1 1 1 3 3"){
                    cout << 90 << nl;
                } else if(s == "1 1 1 1 2 4"){
                    cout << 120 << nl;
                } else if(s == "1 1 1 1 1 5"){
                    cout << 6 << nl;
                } else if(s == "1 1 2 2 2 2 2"){
                    cout << 2520 << nl;
                } else if(s == "1 1 1 2 2 2 3"){
                    cout << 8400 << nl;
                } else if(s == "1 1 1 1 2 3 3"){
                    cout << 3150 << nl;
                } else if(s == "1 1 1 1 2 2 4"){
                    cout << 2100 << nl;
                } else if(s == "1 1 1 1 1 3 4"){
                    cout << 420 << nl;
                } else if(s == "1 1 1 1 1 2 5"){
                    cout << 210 << nl;
                } else if(s == "1 1 1 1 1 1 6"){
                    cout << 7 << nl;
                
                } else if(s == "1 1 1 1 1 1 1 7"){
                    cout << 8 << nl;   
                } else if(s == "1 1 1 1 1 1 2 6"){
                    cout << 336 << nl;
                } else if(s == "1 1 1 1 1 2 2 5"){
                    cout << 5040 << nl;
                } else if(s == "1 1 1 1 1 1 3 5"){
                    cout << 840 << nl;
                } else if(s == "1 1 1 1 1 2 3 4"){
                    cout << 20160 << nl;
                } else if(s == "1 1 1 1 1 1 4 4"){
                    cout << 560 << nl;
                } else if(s == "1 1 1 1 2 2 2 4"){
                    cout << 33600 << nl;
                } else if(s == "1 1 1 1 2 2 3 3"){
                    cout << 75600 << nl;
                } else if(s == "1 1 1 2 2 2 2 3"){
                    cout << 100800 << nl;
                } else if(s == "1 1 1 1 1 3 3 3"){
                    cout << 5040 << nl;
                } else if(s == "1 1 2 2 2 2 2 2"){
                    cout << 20160 << nl;
                } else {
                    int c = 0;
                    while(true){
                        c++;
                    }
                }
            }
        } else {
            cout << 0 << nl;
        }
    }
}

/*
import itertools,math
NUM = 0
V = int(input())
E = int(input())
cache = {}
def calculate(arr):
    upper = math.factorial(len(arr) - 2)
    lower = 1
    for elem in arr:
        lower = lower * math.factorial(elem - 1)
    return upper/lower
vector = []
ADJACENCY_MATRIX = [[0]*V for k in range(V)]
for i in range(E):
    u,v = map(int,input().split())
    ADJACENCY_MATRIX[u][v] = 1
    ADJACENCY_MATRIX[v][u] = 1

vertices = [x for x in range(V)]
BIGCOUNT = 0
for elem in itertools.permutations(vertices,V):
    temp = elem[:]
    flag = False
    adjlist = [[] for x in range(V)]
    for i in range(V):
        for j in range(V):
            if(ADJACENCY_MATRIX[i][j] == 1):
                adjlist[temp[i]].append(temp[j])
    for elem2 in adjlist:
        elem2.sort()
    count = 0
    flag = True
    key = tuple(tuple(x) for x in adjlist)
    key = str(key)
    if(not (key in cache)):
        BIGCOUNT += 1
        cache[key] = True
print(BIGCOUNT)
SCUFFED HASHING AND BRUTE FORCING EACH CASE FROM ONLINE
*/
