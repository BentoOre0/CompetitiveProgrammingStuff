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
        int value;
        SegmentTree* Left;
        SegmentTree* Right;
        void combine_nodes(){
            value = 0;
            if(Left != nullptr){
                value += Left->value;
            }
            if(Right != nullptr){
                value += Right->value;
            }
        }

        int identity(){
            return 0;
        }
    public:
        SegmentTree(vector<int> &arr, int qL, int qR){
            if(qL + 1 == qR){
                value = arr[qL];
                L = qL;
                R = qR;
                Left = nullptr;
                Right = nullptr;
            } else {
                L = qL;
                R = qR;
                Left = nullptr;
                Right = nullptr;
                int M = (qL + qR) >> 1;
                if(qL < M){
                    Left = new SegmentTree(arr, qL, M);
                }
                if(M < qR){
                    Right = new SegmentTree(arr, M, qR);
                }
            }
        }

        int range_query(int qL, int qR){
            if(qL >= qR || qR <= L || qL >= R){
                return identity();
            } else {
                if(L == qL && qR == R){
                    return value;
                } else {
                    int M = (L + R) >> 1;
                    int lval = 0, rval = 0;
                    if(Left != nullptr){
                        lval = Left -> range_query(qL,min(qR,M));
                    }
                    if(Right != nullptr){
                        rval = Right -> range_query(max(M,qL),qR);
                    }
                    return lval + rval;
                }
            }
        }

        void point_update(int id, int val){
            if(id == L && L + 1 == R){
                value = val;
            } else {
                int M = (L + R) >> 1;
                if(id < M){
                    Left -> point_update(id,val);
                }
                if(id >= M){
                    Right -> point_update(id,val);
                }
                combine_nodes();
            }
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    cin >> N >> Q;
    vector<int> array(N,0);
    for(int i = 0; i < N; i++){
        cin >> array[i];
    }
    vector<pii> querylist;
    map<pii, int> queries;
    vector<pii> runningorder;
    int QL, QR;
    for(int i = 0; i < Q; i++){
        cin >> QL >> QR;
        QL--;
        querylist.push_back({QL,QR});
        runningorder.push_back({QL,QR});
    }
    sort(runningorder.begin(), runningorder.end());
    vector<int> SegmentTreearray(N,0);
    map<int,int> lastindex;
    SegmentTree ST = SegmentTree(SegmentTreearray,0,N);
    int index_considered = N - 1;
    for(int q = Q - 1; q >= 0; q--){
        auto [start,end] = runningorder[q];
        while(index_considered >= start){
            if(lastindex.count(array[index_considered])){
                int before = lastindex[array[index_considered]];
                ST.point_update(before, 0);
                ST.point_update(index_considered, 1);
                lastindex[array[index_considered]] = index_considered; 
            } else {
                lastindex[array[index_considered]] = index_considered;
                ST.point_update(index_considered,1);
            }
            index_considered--; 
        }
        queries[{start,end}] = ST.range_query(start,end);
    }    
    for(int i = 0; i < Q; i++){
        cout << queries[querylist[i]] << nl;
    }
}
