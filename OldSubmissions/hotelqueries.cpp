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
        SegmentTree* Left;
        SegmentTree* Right;
        int maxcc;
        
        int identity(){
            return -1;
        }

        void combine_nodes(){
            maxcc = identity();
            if(Left != nullptr){
                maxcc = max(maxcc, Left->maxcc);
            }
            if(Right != nullptr){
                maxcc = max(maxcc, Right->maxcc);
            }
        }

    public:
        SegmentTree(vector<int> &arr, int qL, int qR){
            L = qL;
            R = qR;
            maxcc = identity();
            if(L + 1 == R){
                maxcc = arr[L];
            } else {
                int M = (L + R) >> 1;
                if(qL < M){
                    Left = new SegmentTree(arr, qL, M);
                }
                if(M < qR){
                    Right = new SegmentTree(arr, M, qR);
                }
                combine_nodes();
            }
        }

        int range_query(ll value){
            if(L + 1 == R){
                if(maxcc >= value){
                    return L;
                } else {
                    return -1;
                }
            } else {
                ll qleft = Left->maxcc, qright = Right->maxcc;
                if(qleft >= value && qright >= value){
                    return Left->range_query(value);
                } else if(qleft >= value){
                    return Left->range_query(value);
                } else if(qright >= value){
                    return Right->range_query(value);
                } else {
                    return -1;
                }
            }
        }

        void point_update(int id, int value){
            if(L + 1 == R){
                maxcc = value; //overwrite data
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
    int n, m;
    cin >> n >> m;
    vector<int> hotels(n,0);
    for(int i = 0; i < n; i++){
        cin >> hotels[i];
    }
    SegmentTree root = SegmentTree(hotels,0,n);
    int num;
    for(int i = 0; i < m; i++){
        cin >> num;
        int id = root.range_query(num);
        if(id == -1){
            cout << 0 << sp;
        } else {
            cout << id + 1 << sp;
            hotels[id] -= num;
            root.point_update(id,hotels[id]);
        }
    }
    cout << nl;
}
