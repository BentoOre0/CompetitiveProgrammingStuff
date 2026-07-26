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
        int L, R; //[L,R)
        ll LeftBest, RightBest;
        SegmentTree* Left;
        SegmentTree* Right;
        ll idenity(){
            return 20000000000;
        }
        void combine_nodes(){
            LeftBest = idenity();
            RightBest = idenity();
            int M = (L+R) >> 1;
            if(Left != nullptr){
                LeftBest = min(Left->LeftBest, Right->LeftBest + M - L);
            }
            if(Right != nullptr){
                RightBest = min(Right->RightBest, Left-> RightBest + R - M);
            }
        }
        
    public:
        SegmentTree(int qL, int qR, vector<ll> &arr){
            L = qL;
            R = qR;
            if(L + 1 == R){
                LeftBest = arr[L];
                RightBest = arr[L];
            } else {
                int M = (qL + qR) >> 1;
                Left = new SegmentTree(qL,M,arr);
                Right = new SegmentTree(M,qR,arr);
                combine_nodes();
            }
        }

        ll range_query(int id){
            if(L >= R){
                return idenity();
            }
            if(L + 1 == R){
                return min(LeftBest,RightBest);
            }
            int M = (L + R) >> 1;
            if(id < M){
                ll case1 = Right->LeftBest + (M - id);
                return min(case1, Left->range_query(id));
            } else {
                ll case2 = Left->RightBest + (id - M + 1);
                return min(case2, Right->range_query(id));
            }
        }

        void point_update(int id, ll value){
            if(L + 1 == R){
                LeftBest = value;
                RightBest = value;   
            } else {
                int M = (L + R) >> 1;
                if(id < M){
                    Left->point_update(id,value);
                } else {
                    Right->point_update(id,value);
                }
                combine_nodes();
            }
            
        }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> pizzacost(n,0);
    for(int i = 0; i < n; i++){
        cin >> pizzacost[i];
    }
    SegmentTree root = SegmentTree(0,n, pizzacost);
    int QQ;
    
    for(int i = 0; i < q; i++){
        cin >> QQ;
        if(QQ == 2){
            int id;
            cin >> id;
            id--;
            cout << root.range_query(id) << nl;
        } else {
            int bid, newprice;
            cin >> bid >> newprice;
            bid--;
            root.point_update(bid,newprice);
        }
    }

}
