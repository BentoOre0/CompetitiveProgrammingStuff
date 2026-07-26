#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long long int, long long int>;
const int inf = numeric_limits<int>::max();
const ll INF = numeric_limits<ll>::max();
const char sp = ' ';
const char nl = '\n';


struct SegmentTree{
    private:
        int L, R;
        ll sum, maxprefix, maxsuffix, answer;
        SegmentTree* Left;
        SegmentTree* Right;
        ll identity(){
            return 0;
        }
        void combine_nodes(){
            sum = 0;
            maxprefix = 0;
            maxsuffix = 0;
            answer = 0;
            sum += Left->sum + Right->sum;
            maxprefix = max(Left->maxprefix, Left->sum + Right->maxprefix);
            maxsuffix = max(Right->maxsuffix, Left->maxsuffix + Right->sum);
            answer = max(max(Left->answer, Right->answer), Left->maxsuffix + Right->maxprefix);
        }
    public:
        SegmentTree(vector<ll> &a, int qL, int qR){
            L = qL;
            R = qR;
            if(L + 1 == R){
                sum = a[L];
                maxprefix = a[L];
                maxsuffix = a[L];
                answer = a[L];
                Left = nullptr;
                Right = nullptr;
            } else {
                int M = (L + R) >> 1;
                Left = new SegmentTree(a, qL, M);
                Right = new SegmentTree(a, M, qR);
                combine_nodes();
            }
        }

        void point_update(int idx, ll value){
            if(L + 1 == R){
                sum = value;
                maxprefix = value;
                maxsuffix = value;
                answer = value;
            } else {
                int M = (L + R) >> 1;
                if(idx < M){
                    Left->point_update(idx,value);
                } else if(idx >= M){
                    Right->point_update(idx,value);
                }
                combine_nodes();
            }
        }
        ll ans(){
            ll temp = 0;
            temp = max(temp,answer);
            if(Left != nullptr){
                temp = max(temp, Left->answer);
            }
            if(Right != nullptr){
                temp = max(temp, Right->answer);
            }
            if(Left != nullptr && Right != nullptr){
                temp = max(temp, Left->maxsuffix + Right->maxprefix);
            }
            return temp;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<ll> bruh(n,0);
    for(int i = 0; i < n; i++){
        cin >> bruh[i];
    }
    SegmentTree ST = SegmentTree(bruh, 0, n);
    ll idx, val;
    for(int i = 0; i < m; i++){
        cin >> idx >> val;
        idx--;
        ST.point_update(idx,val);
        cout << ST.ans() << nl;
    }
}
