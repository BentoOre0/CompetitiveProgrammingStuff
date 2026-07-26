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
        int data; //sum of 1's and 0's
        int number; 
        int L, R;
        SegmentTree* Left;
        SegmentTree* Right;

        void combine_node(){
            data = 0;
            if(Left != nullptr){
                data += Left->data;
            }
            if(Right != nullptr){
                data += Right->data;
            }
        }
    public:
        SegmentTree(vector<int> &a, int qL, int qR){
            L = qL;
            R = qR;
            if(L + 1 == R){
                number = a[L];
                data = 1;
            } else {
                number = -1;
                int M = (L + R) >> 1;
                if(L < M){
                    Left = new SegmentTree(a, L, M);   
                }
                if(M < R){
                    Right = new SegmentTree(a, M, R);
                }
                combine_node();   
            }
        }

        int range_query(int qL, int qR, int value){
            // cout << qL << sp << qR << sp << value << sp << data << nl;
            //tree traversal
            if(qR <= qL || L >= qR || R <= qL || value > data || value <= 0){
                return 0;
            } else if(qL + 1 == qR){
                return number;
            } else {
                int M = (qL + qR) >> 1;
                int ldata = Left->data;
                int rdata = Right->data;
                return Left->range_query(qL,min(M,qR),value) + Right->range_query(max(M,qL),qR,value - ldata);
            }
        }
        void point_update(int id){
            if(L + 1 == R){
                data = 0;
                return;
            } else {
                int M = (L + R) >> 1;
                int ldata = Left->data;
                int rdata = Right->data;
                if(id <= ldata){
                    Left->point_update(id);
                } else {
                    Right->point_update(id - ldata);
                }
                combine_node();
            }
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> v(n,0);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int> q(n,0);
    for(int i = 0; i < n; i++){
        cin >> q[i];
    }
    SegmentTree root = SegmentTree(v, 0, v.size());
    // root.point_update(0);
    for(int i = 0; i < q.size(); i++){

        // cout << v[q[i] - 1] << sp << q[i] << nl;
        cout << root.range_query(0,v.size(),q[i]) << sp;
        root.point_update(q[i]);
        // break;
    }
    cout << nl;
    
}
